/*
** Game loop
**
** Created by Stefan Hagdahl
*/

#include "Game.h"

Game::Game(int width, int height)
{
	//Initialise everything
	RMgr = new ResourceMgr();
	mCurrentPiece = NULL;
	mRows = new Rows();
	mPieceBuilder = new PieceBuilder();

	mMap = new Map(10, 20, 304, 124);

	dt = 0.0f;
	// 30 frames per second
	maxFps = 1.0f / 30.0f;
	mSpeed = 1.0f;
	mLevel = 1;
	mSpeedLevel = 1;
	mMenu = new Menu(width, height);
	mStart = mMap->getStartPos();
	mGameState = Meny;
	mScore = 0;
	mDrops = 0;
	mCleared = 0;
	mSpeed = startspeed;
	createInfoLabels();
	mSlidingTime.restart();
	mMusic.openFromFile("sound/Tetris.ogg");
	mMusic.setLoop(true);
	mMusic.setVolume(50.0f);
}

Game::~Game()
{
	// Cleanup
	mMusic.stop();
	delete mMenu;
	delete mCurrentPiece;
	delete mMap;
	delete mPieceBuilder;
	mRows = NULL;
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
			// Rotate piece
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
		else if((mEvent.key.code == Keyboard::A || mEvent.key.code == Keyboard::Left) && pressed)
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
		else if((mEvent.key.code == Keyboard::D || mEvent.key.code == Keyboard::Right) && pressed)
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
		else if((mEvent.key.code == Keyboard::S || mEvent.key.code == Keyboard::Down) && pressed)
		{
			// Move Piece faster downward
			if(mCurrentPiece != NULL && mSpeed != slamspeed)
			{
				mCurrentPiece->setSpeed(slamspeed);
			}
		}
		else if((mEvent.key.code == Keyboard::S || mEvent.key.code == Keyboard::Down) && released)
		{
			// Reset movement speed downwards
			if(mCurrentPiece != NULL)
			{
				mCurrentPiece->setSpeed(mSpeed);
			}
				
		}
		else if(mEvent.key.code == Keyboard::Escape && pressed)
		{
			// Pause game/music and enter menu
			mMusic.pause();
			mGameState = Meny;
			mMenu->setLabel("Paused");
			mMenu->showWindow();
		}
	}
}

void Game::update()
{
	// Check if music is playing, if not start it
	if((mMusic.getStatus() == mMusic.Paused || mMusic.getStatus() == mMusic.Stopped) && mGameState != Meny)
		mMusic.play();
	// Update level
	if(mCleared >= clearedrowsbeforelevel * mLevel && mLevel < maxlevel)
	{
		mCleared = 0;
		mLevel++;
	}
	// Update speed
	if(mDrops >= droppedbeforespeedinc && mSpeed < maxspeed)
	{
		mDrops = 0;
		mSpeed += incspeed;
		mSpeedLevel++;
		if(mCurrentPiece != NULL)
			mCurrentPiece->setSpeed(mSpeed);
	}
	// Update Piece falling
	if(mCurrentPiece != NULL)
	{
		mCurrentPiece->fall(dt);
		// Is the piece colliding with another block?
		if(!mPieceBuilder->isValidMove(*mCurrentPiece))
		{
			// Move piece back to old position and sync with map
			mCurrentPiece->revertMove();
			mMap->syncPiece(*mCurrentPiece);
			// Move piece one row at a time until collision
			while(mPieceBuilder->isValidMove(*mCurrentPiece))
			{
				mCurrentPiece->move(Block::DOWN);
			}
			// Collision as occurred so use old position
			mCurrentPiece->revertMove();
			// Should the piece be released or is sliding still allowed?
			if(mSlidingTime.getElapsedTime().asMilliseconds() > 500)
			{
				// Release the piece into invdiual blocks before creating a new one
				// and drop it on to the map
				mMap->drop(*mCurrentPiece);
				// Use current piece as a starting point for checking if any row has been
				// completed
				mRows->rows = mMap->checkCompleteRow(*mCurrentPiece);
				mPieceBuilder->delPiece(mCurrentPiece);
				mCurrentPiece = NULL;
				// Update Score
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
			// Move piece one row at a time until it's below the map
			while(mMap->isValidMove(*mCurrentPiece))
			{
				mCurrentPiece->move(Block::DOWN);
			}
			// Piece is outside the map so use old position
			mCurrentPiece->revertMove();
			// Should the piece be released or is sliding still allowed?
			if(mSlidingTime.getElapsedTime().asMilliseconds() > 500)
			{
				// Release the piece into invdiual blocks before creating a new one
				// and drop it on to the map
				mMap->drop(*mCurrentPiece);
				// Use current piece as a starting point for checking if any row has been
				// completed
				mRows->rows = mMap->checkCompleteRow(*mCurrentPiece);
				mPieceBuilder->delPiece(mCurrentPiece);
				mCurrentPiece = NULL;
				// Update Score
				mScore += dropped * mLevel;
				mDrops += 1;
			}
		}
		// Check if any row is complete
		if(mRows->rows != NULL)
			checkRows();
	}
	// Update info labels
	mLevelLabel->SetText("Level:" + to_string(mLevel));
	mScoreLabel->SetText("Score:" + to_string(mScore));
	mSpeedLabel->SetText("Speed:" + to_string(mSpeedLevel));
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
		// Draw current piece
		mCurrentPiece->draw(&window);
	}
	// Draw released blocks
	mPieceBuilder->draw(&window);
}

void Game::checkRows()
{
	mRows->nrOfRows = 0;
	mRows->deepest = -1;
	for(int i=0;i<4;i++)
	{
		// Find the deepst cleared row and the number of cleared rows
		if(mRows->rows[i] != -1)
		{
			if(mRows->rows[i] > mRows->deepest)
				mRows->deepest = mRows->rows[i];
			mRows->nrOfRows++;
		}
	}
	// If there are cleared rows then change game state to clearing
	if(mRows->nrOfRows > 0)
		mGameState = Clearing;
	else // If no cleared rows are found, create a new piece and continue the game
	{
		mRows->rows = NULL;
		createPiece();
	}
}

void Game::clearing()
{
	// Remove all cleared rows from the map
	Block** blist;
	for(int i=0; i<4; i++)
	{
		if(mRows->rows[i] != -1)
		{	
			blist = mMap->clearRow(mRows->rows[i]);
			mPieceBuilder->freeBlocks(blist, mMap->getWidth());
			// Increase score by cleared * level
			mScore += cleared * mLevel;
			// Increase cleared rows
			mCleared++;
			// Remove two drops per cleared row
			mDrops -= 2;
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
		// Move each row down 1 row 
		if(droppingClock.getElapsedTime().asMilliseconds() > 500)
		{
			int moveRowNr = -1;
			// Loop over every row from deepest
			for(int i=mRows->deepest; i>=0; i--)
			{
				// Find the first cleared row and break
				for(int j=0; j<4; j++)
				{
					if(mRows->rows[j] == i)
					{
						// Found deepest cleared row
						mRows->rows[j] = -1;
						moveRowNr = i - 1;
						break;
					}
				}
				if(moveRowNr != -1)
					break;
			}
			// Move all rows down one row starting with moveRowNr
			if(moveRowNr != -1)
			{
				mMap->moveBlocks(moveRowNr);
				mRows->nrOfRows--;
				droppingClock.restart();
				// Update remaing cleared rows which has now moved one row down
				for(int i=0; i<4; i++)
				{
					if(mRows->rows[i] != -1)
						mRows->rows[i]++;
				}
			}
		}
	}
	else
	{
		// Go back to playing the game
		mGameState = Playing;
		mRows->rows = NULL;
		mRows->deepest = -1;
		mRows->nrOfRows = 0;
		createPiece();
	}
}

void Game::reset()
{
	// Reset all variables for a new game
	if(mCurrentPiece != NULL)
	{
		mPieceBuilder->delPiece(mCurrentPiece);
		mCurrentPiece = NULL;
	}
	mMap->clearMap();
	mPieceBuilder->reset();
	mScore = 0;
	mDrops = 0;
	mLevel = 1;
	mSpeedLevel = 1;
	mCleared = 0;
	mSpeed = startspeed;
	mMusic.play();
}

void Game::createPiece()
{
	// Create a new piece
	mPiece = (PieceBuilder::Piece)(rand() % 7);
	mCurrentPiece = &mPieceBuilder->addPiece(mPiece, mStart.x, mStart.y);
	mCurrentPiece->setSpeed(mSpeed);
	
	// Check if new piece is colliding with another piece, 
	// if so set game state to GameOver
	if(!mPieceBuilder->isValidMove(*mCurrentPiece))
	{
		mMusic.stop();
		mGameState = GameOver;
		mMenu->setLabel("Game Over");
		mMenu->showWindow();
		mMenu->disableContinueButton();
	}
}

void Game::createInfoLabels()
{
	// Create the labels
	mInfoHeadline = sfg::Label::Create("Info");
	mInfoHeadline->SetId("info");
	mLevelLabel = sfg::Label::Create("Level:");
	mLevelLabel->SetId("level");
	mScoreLabel = sfg::Label::Create("Score:");
	mScoreLabel->SetId("score");
	mSpeedLabel = sfg::Label::Create("Speed:");
	mSpeedLabel->SetId("speed");

	// Create a window
	mWindow = sfg::Window::Create(0);
	mBox = sfg::Box::Create(sfg::Box::VERTICAL);
	mBox->SetSpacing(1.0f);
	mBox->Pack(mInfoHeadline);
	mBox->Pack(mLevelLabel);
	mBox->Pack(mScoreLabel);
	mBox->Pack(mSpeedLabel);

	mWindow->Add(mBox);
	Vector2f size = Vector2f(100.0f, 100.0f);
	float posX = 50.0f;
	float posY = 124.0f;
	mWindow->SetAllocation(FloatRect(Vector2f(posX, posY), size));

	mDesktop.Add(mWindow);
	mDesktop.SetProperty("Label#info", "FontSize", 20);
	mDesktop.SetProperty("Label#level", "FontSize", 20);
	mDesktop.SetProperty("Label#score", "FontSize", 20);
	mDesktop.SetProperty("Label#speed", "FontSize", 20);
}