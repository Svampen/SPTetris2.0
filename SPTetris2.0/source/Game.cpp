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
}

Game::~Game()
{

}

void Game::loop(RenderWindow &window)
{
	//temp stuff start
	mStart = mMap->getStartPos();
	mGameState = Playing;
	//temp stuff end
	while (window.isOpen())
    {
		// Calculate delta time
		dt = mClock.restart().asSeconds();
		dt = min(dt, maxFps);

		while (window.pollEvent(mEvent))
		{
			switch(mEvent.type)
			{
			case Event::Closed:
				// Delete all resources
				window.close();
				break;

			case Event::KeyPressed:
				switch(mGameState)
				{
				case Playing:
					handleinput(true);
					break;
				case Clearing:
					break;
				}
				break;
			case Event::KeyReleased:
				switch(mGameState)
				{
				case Playing:
					handleinput(false);
					break;
				case Clearing:
					break;
				}
				break;
			default:
				break;
			}
		}

		switch(mGameState)
		{
		case Playing:
			update();
			break;
		case Clearing:
			clearing();
			break;
		case Dropping:
			dropping();
			break;
		}

		draw(window);
		window.display();
	}
}

void Game::handleinput(bool pressed)
{
	bool released = false;
	if(!pressed)
		released = true;

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
			//TODO: check against map boundaries
		}
	}
	else if(mEvent.key.code == Keyboard::Num1 && pressed)
	{
		// Release the piece into invdiual blocks before creating a new one
		// and drop it on to the map
		if(mCurrentPiece != NULL)
		{
			mMap->drop(*mCurrentPiece);
			mPieceBuilder->delPiece(mCurrentPiece);
			mCurrentPiece = NULL;
		}
		mCurrentPiece = &mPieceBuilder->addPiece(PieceBuilder::Piece::I, mStart.x, mStart.y);
		mCurrentPiece->setSpeed(mSpeed);
	}
	else if(mEvent.key.code == Keyboard::C && pressed)
	{
		// Release the piece into invdiual blocks before creating a new one
		// and drop it on to the map
		if(mCurrentPiece != NULL)
		{
			mMap->drop(*mCurrentPiece);
			mPieceBuilder->delPiece(mCurrentPiece);
			mCurrentPiece = NULL;
		}
		// Create a new piece
		mPiece = (PieceBuilder::Piece)(rand() % 7);
		mCurrentPiece = &mPieceBuilder->addPiece(mPiece, mStart.x, mStart.y);
		mCurrentPiece->setSpeed(mSpeed);
	}
	else if(mEvent.key.code == Keyboard::A && pressed)
	{
		// Move Piece to the left
		if(mCurrentPiece != NULL)
		{
			mCurrentPiece->move(Block::LEFT);
			if(!mPieceBuilder->isValidMove(*mCurrentPiece))
				mCurrentPiece->revertMove();
			if(!mMap->isValidMove(*mCurrentPiece))
				mCurrentPiece->revertMove();
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
			if(!mMap->isValidMove(*mCurrentPiece))
				mCurrentPiece->revertMove();
		}
	}
	else if(mEvent.key.code == Keyboard::S && pressed)
	{
		// Move Piece faster downward
		if(mCurrentPiece != NULL && mSpeed != 10.0f)
		{
			mSpeed = 10.0f;
			mCurrentPiece->setSpeed(mSpeed);
		}
	}
	else if(mEvent.key.code == Keyboard::S && released)
	{
		if(mCurrentPiece != NULL && mSpeed == 10.0f)
		{
			mSpeed = 1.0f;
			mCurrentPiece->setSpeed(mSpeed);
		}
		else if (mCurrentPiece == NULL)
			mSpeed = 1.0f;
	}
}

void Game::update()
{
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

			// Map should check if rows have be come complete
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
		}
		// Check if any row is complete
		if(mRows->rows != NULL)
			checkRows();
	}
}

void Game::draw(RenderWindow &window)
{
	window.clear(Color::Black);
	//Draw map first
	mMap->draw(&window);
	if(mCurrentPiece)
	{
		mCurrentPiece->draw(&window);
	}
	mPieceBuilder->draw(&window);
	//b->draw(&window);
	//window.draw(*b);
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
		mRows->rows = NULL;
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
	}
}