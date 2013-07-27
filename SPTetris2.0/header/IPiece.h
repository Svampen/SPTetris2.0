#ifndef IPIECE_H
#define IPIECE_H

#include "TetrisPiece.h"

class IPiece : public TetrisPiece
{
public:
	IPiece(float X, float Y);
	IPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3);
	~IPiece();

	void update(float dt);
	void handleInput(float dt);
	void draw(RenderWindow *window);
	void rotate();
	void setPos(float X, float Y);
};

#endif