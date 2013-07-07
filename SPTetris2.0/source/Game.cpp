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

	mMap = new Map(10, 10);

	dt = 0.0f;
	maxFps = 1.0f / 30.0f;
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
					handleinput();
					break;
				case Clearing:
					break;
				}
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
			Block** blist;
			for(int i=0; i<4; i++)
			{
				if(mRows->rows[i] != -1)
				{	
					blist = mMap->clearRow(mRows->rows[i]);
					//FIX ME: should be mMap->getWidth() instead of 10
					mPieceBuilder->freeBlocks(blist, 10);
					//TODO: Trigger particle system here
				}
			}
			mRows = NULL;
			//TODO: Check if anything should fall down before changing game state
			mGameState = Playing;
			break;
		}

		draw(window);
		window.display();
	}
}

void Game::handleinput()
{
	switch(mEvent.key.code)
	{
	case Keyboard::Space:
		if(mCurrentPiece != NULL)
		{
			mCurrentPiece->rotate();
			if(!mPieceBuilder->isValidMove(*mCurrentPiece))
			{
				mCurrentPiece->revertMove();
				mCurrentPiece->setOldRotationStage();
			}
		}
		break;
	case Keyboard::Num1:
		// Release the piece into invdiual blocks before creating a new one
		// and drop it on to the map
		if(mCurrentPiece != NULL)
		{
			mMap->drop(*mCurrentPiece);
			mPieceBuilder->delPiece(mCurrentPiece);
			mCurrentPiece = NULL;
		}
		mCurrentPiece = &mPieceBuilder->addPiece(PieceBuilder::Piece::I, mStart.x, mStart.y);
		break;
	case Keyboard::C:
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
		break;
	case Keyboard::A:
		// Move Piece to the left
		if(mCurrentPiece != NULL)
		{
			mCurrentPiece->move(TetrisPiece::LEFT);
			if(!mPieceBuilder->isValidMove(*mCurrentPiece))
				mCurrentPiece->revertMove();
			if(!mMap->isValidMove(*mCurrentPiece))
				mCurrentPiece->revertMove();
		}
		break;
	case Keyboard::D:
		// Move Piece to the right
		if(mCurrentPiece != NULL)
		{
			mCurrentPiece->move(TetrisPiece::RIGHT);
			if(!mPieceBuilder->isValidMove(*mCurrentPiece))
				mCurrentPiece->revertMove();
			if(!mMap->isValidMove(*mCurrentPiece))
				mCurrentPiece->revertMove();
		}
		break;
	default:
		break;
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
				mCurrentPiece->move(TetrisPiece::DOWN);
			}
			// use old pos
			mCurrentPiece->revertMove();
			// Release the piece into invdiual blocks before creating a new one
			// and drop it on to the map
			mMap->drop(*mCurrentPiece);
			// Use current piece as a starting point for check if any row has been
			// completed
			mRows->rows = mMap->checkCompleteRow(*mCurrentPiece);
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
				mCurrentPiece->move(TetrisPiece::DOWN);
			}
			// use old pos
			mCurrentPiece->revertMove();
			// Release the piece into invdiual blocks before creating a new one
			// and drop it on to the map
			mMap->drop(*mCurrentPiece);
			// Use current piece as a starting point for check if any row has been
			// completed
			mRows->rows = mMap->checkCompleteRow(*mCurrentPiece);
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
}