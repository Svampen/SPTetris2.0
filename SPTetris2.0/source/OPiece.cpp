/* OPiece class
** Tetris block shaped as a 'O'
** Rotation Stages
**  1
**  _ _
** |_|_|
** |_|_|
** Created by Stefan Hagdahl
*/

#include "OPiece.h"

OPiece::OPiece(float X, float Y)
{
	// Create block used for OPiece
	mBlock0 = new Block(X, Y);
	mBlock1 = new Block(X, Y);
	mBlock2 = new Block(X, Y);
	mBlock3 = new Block(X, Y);
	mOldRotationStage = 1;
	mRotationStage = 1;
	setPos(X, Y);
}
OPiece::OPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3)
{
	mBlock0 = b0;
	mBlock1 = b1;
	mBlock2 = b2;
	mBlock3 = b3;
	mOldRotationStage = 1;
	mRotationStage = 1;
	setPos(X, Y);
}

OPiece::~OPiece()
{
	delete mBlock0;
	delete mBlock1;
	delete mBlock2;
	delete mBlock3;
}
void OPiece::update(float dt)
{
}
void OPiece::handleInput(float dt)
{
}
void OPiece::draw(RenderWindow *window)
{
	window->draw(*mBlock0);
	window->draw(*mBlock1);
	window->draw(*mBlock2);
	window->draw(*mBlock3);
}
void OPiece::rotate()
{
	// OPiece doesn't rotate
}
void OPiece::setPos(float X, float Y)
{
	Vector2f size = mBlock0->getSize();

	mBlock0->setPos(X, Y);
	mBlock1->setPos(X + size.x * 1, Y);
	mBlock2->setPos(X, Y + size.y * 1);
	mBlock3->setPos(X + size.x * 1, Y + size.y * 1);
}