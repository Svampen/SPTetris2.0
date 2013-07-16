/*
** Game loop
**
** Created by Stefan Hagdahl
*/

#include "Game.h"

Game::Game()
{
	mCurrentPiece = NULL;
	mRows = new Rows();
	mPieceBuilder = new PieceBuilder();

	mMap = new Map(10, 15);

	dt = 0.0f;
	// 30 frames per second
	maxFps = 1.0f / 30.0f;
	mSpeed = 1.0f;
	mLevel = 1;
	mMenu = new Menu(1280, 720);
	mStart = mMap->getStartPos();
	mGameState = Meny;
	mScore = 0;
	mDrops = 0;
	createInfoLabels();
	mSlidingTime.restart();
}

Game::~Game()
{
	delete mMenu;
}

void Game::loop(RenderWindow &window)
{
	window.resetGLStates();
	while (window.isOpen())
    {
		window.clear(Color::Black);
		// Calculate delta time
		dt = mClock.restart().asSeconds();
		dt = min(dt, maxFps);
		switch(mGameState)
		{
		case Meny:
			// handle input
			mGameState = mMenu->handleInput(mEvent, window);
			// update
			mMenu->update(dt);
			// draw
			mMenu->draw(window);
			break;
		case Playing:
			// handle input
			handleinput(window);
			//s temp
			cout << "Score:" << mScore << "\n";
			cout << "Level:" << mLevel << "\n";
			cout << "Drops:" << mDrops << "\n";
			//e temp
			// update
			update();
			// draw
			draw(window);
			break;
		case Clearing:
			// handle input
			// update
			clearing();
			// draw
			draw(window);
			break;
		case Dropping:
			// handle input
			// update
			dropping();
			// draw
			draw(window);
			break;
		case Paused:
			// handle input
			// update
			// draw
			draw(window);
			break;
		case New:
			// Reset everything
			reset();
			mGameState = Playing;
			createPiece();
			draw(window);
			break;
		case Quit:
			// Delete all resources
			window.close();
			break;
		case GameOver:
			// handle input
			mGameState = mMenu->handleInput(mEvent, window);
			// update
			mMenu->update(dt);
			// draw
			mMenu->draw(window);
			break;
		}
		window.display();
	}
}

void Game::handleinput(RenderWindow &window)
{
	bool pressed = false;
	bool released = false;

	while (window.pollEvent(mEvent))
	{
		pressed = false;
		released = false;

		switch(mEvent.type)
		{
		case Event::Closed:
			// Delete all resources
			window.close();
			break;
		case Event::KeyPressed:
			pressed = true;
			break;
		case Event::KeyReleased:
			released = true;
			break;
		default:
			break;
		}

		if(mEvent.key.code == Keyboard::Space && pressed)
		{
			if(mCurrentPiece != NULL)
			{
				mCurrentPiece->rotate();
				if(!mPieceBuilder->isValidMove(*mCurrentPiece))
				{
					mCurrentPiece->revertMove();
					mCurrentPiece->setOldRotationStage();
				}
				if(!mMap->isValidMove(*mCurrentPiece))
				{
					mCurrentPiece->revertMove();
					mCurrentPiece->setOldRotationStage();
				}
			}
		}
		else if(mEvent.key.code == Keyboard::A && pressed)
		{
			// Move Piece to the left
			if(mCurrentPiece != NULL)
			{
				mCurrentPiece->move(Block::LEFT);
				if(!mPieceBuilder->isValidMove(*mCurrentPiece))
					mCurrentPiece->revertMove();
				else
					mSlidingTime.restart();
				if(!mMap->isValidMove(*mCurrentPiece))
					mCurrentPiece->revertMove();
				else
					mSlidingTime.restart();
			}
		}
		else if(mEvent.key.code == Keyboard::D && pressed)
		{
			// Move Piece to the right
			if(mCurrentPiece != NULL)
			{
				mCurrentPiece->move(Block::RIGHT);
				if(!mPieceBuilder->isValidMove(*mCurrentPiece))
					mCurrentPiece->revertMove();
				else
					mSlidingTime.restart();
				if(!mMap->isValidMove(*mCurrentPiece))
					mCurrentPiece->revertMove();
				else
					mSlidingTime.restart();
			}
		}
		else if(mEvent.key.code == Keyboard::S && pressed)
		{
			// Move Piece faster downward
			if(mCurrentPiece != NULL && speed * mLevel != maxspeed)
			{
				mCurrentPiece->setSpeed(maxspeed);
			}
		}
		else if(mEvent.key.code == Keyboard::S && released)
		{
			if(mCurrentPiece != NULL)
			{
				mCurrentPiece->setSpeed(speed * mLevel);
			}
				
		}
		else if(mEvent.key.code == Keyboard::Escape && pressed)
		{
			mGameState = Meny;
			mMenu->setLabel("Paused");
			mMenu->showWindow();
		}
	}
}

void Game::update()
{
	// Update level and speed
	if(mDrops >= dropsPerLevel * mLevel && mLevel < maxlevel)
	{
		mDrops = 0;
		mLevel += 1;
		if(mCurrentPiece != NULL)
			mCurrentPiece->setSpeed(speed * mLevel);
	}
	// Update info labels
	mLevelLabel->SetText("Level:" + to_string(mLevel));
	mScoreLabel->SetText("Score:" + to_string(mScore));
	// Update Piece falling
	if(mCurrentPiece != NULL)
	{
		mCurrentPiece->fall(dt);
		// Is the piece colliding with another block?
		if(!mPieceBuilder->isValidMove(*mCurrentPiece))
		{
			// Move back to old position and sync with map
			mCurrentPiece->revertMove();
			mMap->syncPiece(*mCurrentPiece);
			// Move piece one tile at a time until collision
			while(mPieceBuilder->isValidMove(*mCurrentPiece))
			{
				mCurrentPiece->move(Block::DOWN);
			}
			// use old pos
			mCurrentPiece->revertMove();
			// Should the piece be released or is sliding still allowed?
			if(mSlidingTime.getElapsedTime().asMilliseconds() > 500)
			{
				// Release the piece into invdiual blocks before creating a new one
				// and drop it on to the map
				mMap->drop(*mCurrentPiece);
				// Use current piece as a starting point for check if any row has been
				// completed
				mRows->rows = mMap->checkCompleteRow(*mCurrentPiece);
				mRows->cleared = new bool[];
				for(int i=0; i<4; i++)
					mRows->cleared[i] = false;
				mPieceBuilder->delPiece(mCurrentPiece);
				mCurrentPiece = NULL;
				// Score
				mScore += dropped * mLevel;
				mDrops += 1;
			}
		}
		// Is the piece below the map?
		else if(!mMap->isValidMove(*mCurrentPiece))
		{
			// Move back to last position and sync with map
			mCurrentPiece->revertMove();
			mMap->syncPiece(*mCurrentPiece);
			// move piece one tile at a time until last outside map then
			while(mMap->isValidMove(*mCurrentPiece))
			{
				mCurrentPiece->move(Block::DOWN);
			}
			// use old pos
			mCurrentPiece->revertMove();
			// Should the piece be released or is sliding still allowed?
			if(mSlidingTime.getElapsedTime().asMilliseconds() > 500)
			{
				// Release the piece into invdiual blocks before creating a new one
				// and drop it on to the map
				mMap->drop(*mCurrentPiece);
				// Use current piece as a starting point for check if any row has been
				// completed
				mRows->rows = mMap->checkCompleteRow(*mCurrentPiece);
				mRows->cleared = new bool[];
				for(int i=0; i<4; i++)
					mRows->cleared[i] = false;
				mPieceBuilder->delPiece(mCurrentPiece);
				mCurrentPiece = NULL;
				// Score
				mScore += dropped * mLevel;
				mDrops += 1;
			}
		}
		// Check if any row is complete
		if(mRows->rows != NULL)
			checkRows();
	}

	// Update info labels
	mDesktop.Update(dt);
}

void Game::draw(RenderWindow &window)
{
	
	
	// Draw info labels
	mSfgui.Display(window);

	//Draw map first
	mMap->draw(&window);
	if(mCurrentPiece)
	{
		mCurrentPiece->draw(&window);
	}
	mPieceBuilder->draw(&window);
}

void Game::checkRows()
{
	mRows->nrOfRows = 0;
	mRows->deepest = -1;
	for(int i=0;i<4;i++)
	{
		if(mRows->rows[i] != -1)
		{
			if(mRows->rows[i] > mRows->deepest)
				mRows->deepest = mRows->rows[i];
			mRows->nrOfRows++;
		}
	}
	if(mRows->nrOfRows > 0)
		mGameState = Clearing;
	else
	{
		mRows->rows = NULL;
		createPiece();
	}
}

void Game::clearing()
{
	Block** blist;
	for(int i=0; i<4; i++)
	{
		if(mRows->rows[i] != -1)
		{	
			blist = mMap->clearRow(mRows->rows[i]);
			mPieceBuilder->freeBlocks(blist, mMap->getWidth());
			// Increase score by cleared * level
			mScore += cleared * mLevel;
			// Remove one drops per cleared row
			mDrops -= 1;
			//TODO: Trigger particle system here
		}
	}
	droppingClock.restart();
	mGameState = Dropping;
}

void Game::dropping()
{
	if(mRows->rows == NULL)
	{
		mGameState = Playing;
		createPiece();
	}
	else if(mRows->nrOfRows > 0 && mRows->deepest > 0)
	{
		//Move each row down 1 row per second
		if(droppingClock.getElapsedTime().asMilliseconds() > 500)
		{
			int moveRowNr = -1;
			bool clearedRow;
			int prevEmptyRow = -1;
			for(int i=mRows->deepest; i>=0; i--)
			{
				clearedRow = false;
				for(int j=0; j<4; j++)
				{
					// Check if row exists as a cleared row
					if(i == mRows->rows[j])
					{
						clearedRow = true;
						prevEmptyRow = j;
						break;
					}

				}
				// If current row isn't cleared and
				// no other row has been set as deepest noncleared row
				// then set it as such
				if(!clearedRow && moveRowNr == -1)
				{
					if(prevEmptyRow != -1)
						// Change status on previously empty
						// row to not empty anymore as it will be
						// filled with blocks
						mRows->rows[prevEmptyRow] = -1;
					moveRowNr = i;
				}
				// If current row is empty and a noncleared
				// row has been set then this row has moved 
				// down a row
				else if(clearedRow && moveRowNr != -1)
				{
					mRows->rows[prevEmptyRow]--;
				}
			}

			if(moveRowNr != -1)
			{
				mMap->moveBlocks(moveRowNr);
				mRows->nrOfRows--;
				droppingClock.restart();
			}
		}
	}
	else
	{
		// Go back to playing the game
		mGameState = Playing;
		mRows->rows = NULL;
		mRows->cleared = NULL;
		mRows->deepest = -1;
		mRows->nrOfRows = 0;
		createPiece();
	}
}

void Game::reset()
{
	if(mCurrentPiece != NULL)
	{
		mPieceBuilder->delPiece(mCurrentPiece);
		mCurrentPiece = NULL;
	}
	mMap->clearMap();
	mPieceBuilder->reset();
	mScore = 0;
	mDrops = 0;
	mLevel = 0;
}

void Game::createPiece()
{
	// Create a new piece
	mPiece = (PieceBuilder::Piece)(rand() % 7);
	mCurrentPiece = &mPieceBuilder->addPiece(mPiece, mStart.x, mStart.y);
	mCurrentPiece->setSpeed(speed * mLevel);
	
	// Check if new piece is colliding with another piece, 
	// if so set mGameState to GameOver
	if(!mPieceBuilder->isValidMove(*mCurrentPiece))
	{
		mGameState = GameOver;
		mMenu->setLabel("Game Over");
		mMenu->showWindow();
		mMenu->disableContinueButton();
	}
}

void Game::createInfoLabels()
{
	// Create the labels
	mInfoHeadline = sfg::Label::Create("Score and Level");
	mInfoHeadline->SetId("info");
	mLevelLabel = sfg::Label::Create("Level:");
	mLevelLabel->SetId("level");
	mScoreLabel = sfg::Label::Create("Score:");
	mScoreLabel->SetId("score");

	// Create a window and add the label to it. Also set the window's title.
	mWindow = sfg::Window::Create(0);
	mBox = sfg::Box::Create(sfg::Box::VERTICAL);
	mBox->SetSpacing(1.0f);
	mBox->Pack(mInfoHeadline);
	mBox->Pack(mLevelLabel);
	mBox->Pack(mScoreLabel);

	mWindow->Add(mBox);
	Vector2f size = Vector2f(100.0f, 100.0f);
	float posX = 400.0f;
	float posY = 20.0f;
	mWindow->SetAllocation(FloatRect(Vector2f(posX, posY), size));

	mDesktop.Add(mWindow);
	mDesktop.SetProperty("Label#info", "FontSize", 20);
	mDesktop.SetProperty("Label#level", "FontSize", 20);
	mDesktop.SetProperty("Label#score", "FontSize", 20);
}