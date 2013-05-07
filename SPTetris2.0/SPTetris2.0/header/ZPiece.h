#ifndef ZPIECE_H
#define ZPIECE_H

#include "TetrisPiece.h"

class ZPiece : public TetrisPiece
{
public:
	ZPiece(float X, float Y);
	ZPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3);
	~ZPiece();

	void onLostDevice();
	void onResetDevice();
	void update(float dt);
	void handleInput(float dt);
	void draw(RenderWindow *window);
	void rotate();
	void setPos(float X, float Y);
};

#endif