/*
** Game loop
**
** Created by Stefan Hagdahl
*/

#include "Game.h"

Game::Game()
{
	mCurrentPiece = NULL;
	mPieceBuilder = new PieceBuilder();

	mMap = new Map(20, 30);

	dt = 0.0f;
	maxFps = 1.0f / 30.0f;
}

Game::~Game()
{

}

void Game::loop(RenderWindow &window)
{
	//temp stuff start
	Vector2f start = mMap->getStartPos();
	//temp stuff end
	while (window.isOpen())
    {
		dt = mClock.restart().asMilliseconds() / 1000.0f;
		dt = min(dt, maxFps);

        Event event;
        while (window.pollEvent(event))
        {
			switch(event.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::KeyPressed:
				switch(event.key.code)
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
					mCurrentPiece = &mPieceBuilder->addPiece(mPiece, start.x, start.y);
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
			default:
				break;
			}

        }

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
				mPieceBuilder->delPiece(mCurrentPiece);
				mCurrentPiece = NULL;
				
			}

		}
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

		window.display();
    }
}

void Game::handleinput()
{

}

void Game::draw()
{

}