#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "IPiece.h"
#include "PieceBuilder.h"
#include "Map.h"
#include "Menu.h"

class Game
{
public:
	Game();
	~Game();

	void loop(RenderWindow &window);

private:

	void handleinput(RenderWindow &window);
	void update();
	void draw(RenderWindow &window);
	void checkRows();
	void clearing();
	void dropping();
	void reset();

	TetrisPiece *mCurrentPiece;
	PieceBuilder *mPieceBuilder;
	Map *mMap;
	Menu *mMenu;
	
	float mSpeed;

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
		bool *cleared;
		int nrOfRows;
		int deepest;
	};
	Rows *mRows;
	sf::Clock droppingClock;
};

#endif