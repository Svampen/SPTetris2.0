#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "IPiece.h"
#include "PieceBuilder.h"
#include "Map.h"

class Game
{
public:
	Game();
	~Game();

	void loop(RenderWindow &window);

private:

	void handleinput();
	void update();
	void draw(RenderWindow &window);
	void checkRows();
	void clearing();
	void dropping();


	TetrisPiece *mCurrentPiece;
	PieceBuilder *mPieceBuilder;
	Map *mMap;
	
	enum GameState
	{
		Paused     = 0,
		Playing    = 1,
		Clearing   = 2,
		Dropping   = 3,
		Meny       = 4
	};

	sf::Clock mClock;
	Event mEvent;
	float dt;
	float maxFps;
	PieceBuilder::Piece mPiece;
	GameState mGameState;
	Vector2f mStart;
	struct Rows
	{
		int *rows;
		int nrOfRows;
		int deepest;
	};
	Rows *mRows;
	sf::Clock droppingClock;
};

#endif