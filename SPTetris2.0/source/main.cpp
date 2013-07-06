#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Block.h"
#include "IPiece.h"
#include "PieceBuilder.h"

using namespace sf;

int main()
{
	// Hide console window
	HWND hWnd = GetConsoleWindow(); 
    ShowWindow( hWnd, SW_HIDE );
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(1280, 720), "SPTetris 2.0", Style::Close, ContextSettings());
	//Block *b = new Block(0.0f, 0.0f, 0.0f);
	TetrisPiece *p = NULL;
	PieceBuilder *mPieceBuilder = new PieceBuilder();
	PieceBuilder::Piece piece;
	srand((unsigned int)time(NULL));
	float startX = 100.0;
	float startY = 100.0f;
	//IPiece *b = new IPiece(100.0f, 100.0f);
    while (window.isOpen())
    {
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
					if(p != NULL)
					{
						p->rotate();
						if(!mPieceBuilder->isValidMove(*p))
						{
							p->revertMove();
							p->setOldRotationStage();
						}
						
					}
					break;
				case Keyboard::C:
					// Release the piece into invdiual blocks before creating a new one
					if(p != NULL)
					{
						mPieceBuilder->delPiece(p);
						p = NULL;
					}
					// Create a new piece
					piece = (PieceBuilder::Piece)(rand() % 7);
					p = &mPieceBuilder->addPiece(piece, startX, startY);
					break;
				case Keyboard::A:
					// Move Piece to the left
					if(p != NULL)
					{
						p->move(TetrisPiece::LEFT);
						if(!mPieceBuilder->isValidMove(*p))
							p->revertMove();
					}
					break;
				case Keyboard::D:
					// Move Piece to the right
					if(p != NULL)
					{
						p->move(TetrisPiece::RIGHT);
						if(!mPieceBuilder->isValidMove(*p))
							p->revertMove();
					}
					break;
				default:
					break;
				}
			default:
				break;
			}

        }

		window.clear(Color::Black);
		if(p)
		{
			p->draw(&window);
		}
		mPieceBuilder->draw(&window);
		//b->draw(&window);
		//window.draw(*b);

		window.display();
    }

    return 0;
}