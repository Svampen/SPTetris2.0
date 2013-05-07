#ifndef OPIECE_H
#define OPIECE_H

#include "TetrisPiece.h"

class OPiece : public TetrisPiece
{
public:
	OPiece(float X, float Y);
	OPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3);
	~OPiece();

	void onLostDevice();
	void onResetDevice();
	void update(float dt);
	void handleInput(float dt);
	void draw(RenderWindow *window);
	void rotate();
	void setPos(float X, float Y);
};

#endif