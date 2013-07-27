#ifndef LPIECE_H
#define LPIECE_H

#include "TetrisPiece.h"

class LPiece : public TetrisPiece
{
public:
	LPiece(float X, float Y);
	LPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3);
	~LPiece();

	void update(float dt);
	void handleInput(float dt);
	void draw(RenderWindow *window);
	void rotate();
	void setPos(float X, float Y);
};

#endif