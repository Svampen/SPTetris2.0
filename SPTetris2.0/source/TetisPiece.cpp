/* TetrisPiece class
** Super class to all tetris pieces
**
** Created by Stefan Hagdahl
*/

#include "TetrisPiece.h"

TetrisPiece::TetrisPiece()
{
	mFallSpeedPerFps = 26.0f;
}
TetrisPiece::~TetrisPiece()
{
}
void TetrisPiece::move(DIR Dir)
{
	Vector2f size = mBlock0->getSize();
	float X = 0.0f;
	switch(Dir)
	{
	case LEFT:
		X -= (size.x * 1);
		mBlock0->moveX(X);
		mBlock1->moveX(X);
		mBlock2->moveX(X);
		mBlock3->moveX(X);
		break;
	case RIGHT:
		X += size.x * 1;
		mBlock0->moveX(X);
		mBlock1->moveX(X);
		mBlock2->moveX(X);
		mBlock3->moveX(X);
		break;
	}
}

void TetrisPiece::fall(float dt)
{
	float speed = mFallSpeedPerFps * dt;
	mBlock0->moveY(speed);
	mBlock1->moveY(speed);
	mBlock2->moveY(speed);
	mBlock3->moveY(speed);
}

void TetrisPiece::revertMove()
{
	mBlock0->setOldPos();
	mBlock1->setOldPos();
	mBlock2->setOldPos();
	mBlock3->setOldPos();
}

void TetrisPiece::setOldRotationStage()
{
	mRotationStage = mOldRotationStage;
}