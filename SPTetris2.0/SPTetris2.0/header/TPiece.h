#ifndef TPIECE_H
#define TPIECE_H

#include "TetrisPiece.h"

class TPiece : public TetrisPiece
{
public:
	TPiece(float X, float Y);
	TPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3);
	~TPiece();

	void onLostDevice();
	void onResetDevice();
	void update(float dt);
	void handleInput(float dt);
	void draw(RenderWindow *window);
	void rotate();
	void setPos(float X, float Y);
};

#endif