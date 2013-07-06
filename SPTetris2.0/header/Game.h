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


	TetrisPiece *mCurrentPiece;
	PieceBuilder *mPieceBuilder;
	Map *mMap;
	
	
	sf::Clock mClock;
	Event mEvent;
	float dt;
	float maxFps;
	PieceBuilder::Piece mPiece;
	Vector2f mStart;
};

#endif