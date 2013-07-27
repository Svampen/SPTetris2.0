/* LPiece class
** Tetris block shaped as a 'L'
** Rotation Stages
**   1        2        3       4
**   _               _ _         _
**  |_|     _ _ _   |_|_|    _ _|_|
**  |_|_   |_|_|_|    |_|   |_|_|_|
**  |_|_|  |_|        |_|   
**
** Created by Stefan Hagdahl
*/

#include "LPiece.h"

LPiece::LPiece(float X, float Y)
{
	// Create block used for LPiece
	// starting with the center piece that will not rotate
	mBlock0 = new Block(X, Y);
	mBlock1 = new Block(X, Y);
	mBlock2 = new Block(X, Y);
	mBlock3 = new Block(X, Y);
	mBlock0->setTex("gfx/orange.png");
	mBlock1->setTex("gfx/orange.png");
	mBlock2->setTex("gfx/orange.png");
	mBlock3->setTex("gfx/orange.png");
	mOldRotationStage = 1;
	mRotationStage = 1;
	setPos(X, Y);
}

LPiece::LPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3)
{
	mBlock0 = b0;
	mBlock1 = b1;
	mBlock2 = b2;
	mBlock3 = b3;
	mBlock0->setTex("gfx/orange.png");
	mBlock1->setTex("gfx/orange.png");
	mBlock2->setTex("gfx/orange.png");
	mBlock3->setTex("gfx/orange.png");
	mOldRotationStage = 1;
	mRotationStage = 1;
	setPos(X, Y);
}

LPiece::~LPiece()
{
	delete mBlock0;
	delete mBlock1;
	delete mBlock2;
	delete mBlock3;
}
void LPiece::update(float dt)
{
}
void LPiece::handleInput(float dt)
{
}
void LPiece::draw(RenderWindow *window)
{
	window->draw(*mBlock0);
	window->draw(*mBlock1);
	window->draw(*mBlock2);
	window->draw(*mBlock3);
}
void LPiece::rotate()
{
	// Move blocks based on center block
	float X = mBlock0->getX();
	float Y = mBlock0->getY();
	Vector2f size = mBlock0->getSize();
	switch(mRotationStage)
	{
	case 1: // Move blocks to rotationStage 2 if allowed
		mOldRotationStage = mRotationStage;
		mRotationStage = 2;
		setPos(X,Y);
		break;
	case 2: // Move blocks to rotationStage 3 if allowed
		mOldRotationStage = mRotationStage;
		mRotationStage = 3;
		setPos(X,Y);
		break;
	case 3: // Move blocks to rotationStage 4 if allowed
		mOldRotationStage = mRotationStage;
		mRotationStage = 4;
		setPos(X,Y);
		break;
	case 4: // Move blocks to rotationStage 1 if allowed
		mOldRotationStage = mRotationStage;
		mRotationStage = 1;
		setPos(X,Y);
		break;
	}
}

void LPiece::setPos(float X, float Y)
{
	Vector2f size = mBlock0->getSize();
	switch(mRotationStage)
	{
	case 1:
		mBlock0->move(X, Y);
		mBlock1->move(X, Y - size.y * 1);
		mBlock2->move(X, Y + size.y * 1);
		mBlock3->move(X+size.x * 1, Y + size.y * 1);
		break;
	case 2:
		mBlock0->move(X, Y);
		mBlock1->move(X+size.x * 1, Y);
		mBlock2->move(X-size.x * 1, Y);
		mBlock3->move(X-size.x * 1, Y + size.y * 1);
		break;
	case 3:
		mBlock0->move(X, Y);
		mBlock1->move(X, Y + size.y * 1);
		mBlock2->move(X, Y - size.y * 1);
		mBlock3->move(X-size.x * 1, Y - size.y * 1);
		break;
	case 4:
		mBlock0->move(X, Y);
		mBlock1->move(X-size.x * 1, Y);
		mBlock2->move(X+size.x * 1, Y);
		mBlock3->move(X+size.x * 1, Y - size.y * 1);
		break;
	}
}