/* TetrisPiece class
** Super class to all tetris pieces
**
** Created by Stefan Hagdahl
*/

#include "TetrisPiece.h"

TetrisPiece::TetrisPiece()
{
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