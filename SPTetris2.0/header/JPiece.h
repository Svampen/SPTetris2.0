#ifndef JPIECE_H
#define JPIECE_H

#include "TetrisPiece.h"

class JPiece : public TetrisPiece
{
public:
	JPiece(float X, float Y);
	JPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3);
	~JPiece();

	void update(float dt);
	void handleInput(float dt);
	void draw(RenderWindow *window);
	void rotate();
	void setPos(float X, float Y);
};

#endif