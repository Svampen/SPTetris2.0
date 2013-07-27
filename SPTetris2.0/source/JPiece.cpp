/* JPiece class
** Tetris block shaped as a 'J'
** Rotation Stages
**    1     2     3       4
**    _   _       _ _
**   |_| |_|_ _  |_|_|  _ _ _
**  _|_| |_|_|_| |_|   |_|_|_|
** |_|_|         |_|       |_|
**
** Created by Stefan Hagdahl
*/

#include "JPiece.h"

JPiece::JPiece(float X, float Y)
{
	// Create block used for JPiece
	mBlock0 = new Block(X, Y);
	mBlock1 = new Block(X, Y);
	mBlock2 = new Block(X, Y);
	mBlock3 = new Block(X, Y);
	mBlock0->setTex("gfx/blue.png");
	mBlock1->setTex("gfx/blue.png");
	mBlock2->setTex("gfx/blue.png");
	mBlock3->setTex("gfx/blue.png");
	mOldRotationStage = 1;
	mRotationStage = 1;
	setPos(X, Y);
}

JPiece::JPiece(float X, float Y, Block *b0, Block *b1, Block *b2, Block *b3)
{
	mBlock0 = b0;
	mBlock1 = b1;
	mBlock2 = b2;
	mBlock3 = b3;
	mBlock0->setTex("gfx/blue.png");
	mBlock1->setTex("gfx/blue.png");
	mBlock2->setTex("gfx/blue.png");
	mBlock3->setTex("gfx/blue.png");
	mOldRotationStage = 1;
	mRotationStage = 1;
	setPos(X, Y);
}

JPiece::~JPiece()
{
	delete mBlock0;
	delete mBlock1;
	delete mBlock2;
	delete mBlock3;
}
void JPiece::update(float dt)
{
}
void JPiece::handleInput(float dt)
{
}
void JPiece::draw(RenderWindow *window)
{
	window->draw(*mBlock0);
	window->draw(*mBlock1);
	window->draw(*mBlock2);
	window->draw(*mBlock3);
}
void JPiece::rotate()
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
		setPos(X, Y);
		break;
	case 2: // Move blocks to rotationStage 3 if allowed
		mOldRotationStage = mRotationStage;
		mRotationStage = 3;
		setPos(X, Y);
		break;
	case 3: // Move blocks to rotationStage 4 if allowed
		mOldRotationStage = mRotationStage;
		mRotationStage = 4;
		setPos(X, Y);
		break;
	case 4: // Move blocks to rotationStage 1 if allowed
		mOldRotationStage = mRotationStage;
		mRotationStage = 1;
		setPos(X, Y);
		break;
	}
}

void JPiece::setPos(float X, float Y)
{
	Vector2f size = mBlock0->getSize();
	switch(mRotationStage)
	{
	case 1:
		mBlock0->move(X, Y);
		mBlock1->move(X, Y - size.y * 1);
		mBlock2->move(X, Y + size.y * 1);
		mBlock3->move(X-size.x * 1, Y + size.y * 1);
		break;
	case 2:
		mBlock0->move(X, Y);
		mBlock1->move(X+size.x * 1, Y);
		mBlock2->move(X-size.x * 1, Y);
		mBlock3->move(X-size.x * 1, Y - size.y * 1);
		break;
	case 3:
		mBlock0->move(X, Y);
		mBlock1->move(X, Y + size.y * 1);
		mBlock2->move(X, Y - size.y * 1);
		mBlock3->move(X+size.x * 1, Y - size.y * 1);
		break;
	case 4:
		mBlock0->move(X, Y);
		mBlock1->move(X-size.x * 1, Y);
		mBlock2->move(X+size.x * 1, Y);
		mBlock3->move(X+size.x * 1, Y + size.y * 1);
		break;
	}
}