#ifndef SPIECE_H
#define SPIECE_H

#include "TetrisPiece.h"

class SPiece : public TetrisPiece
{
public:
	SPiece(float X, float Y);
	SPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3);
	~SPiece();

	void update(float dt);
	void handleInput(float dt);
	void draw(RenderWindow *window);
	void rotate();
	void setPos(float X, float Y);
};

#endif