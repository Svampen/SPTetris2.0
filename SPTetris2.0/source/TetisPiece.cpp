/* TetrisPiece class
** Super class to all tetris pieces
**
** Created by Stefan Hagdahl
*/

#include "TetrisPiece.h"

TetrisPiece::TetrisPiece()
{
	mFallSpeedPerFps = 26.0f * 2.0f;
}
TetrisPiece::~TetrisPiece()
{
}
void TetrisPiece::move(Block::DIR Dir)
{
	mBlock0->move(Dir);
	mBlock1->move(Dir);
	mBlock2->move(Dir);
	mBlock3->move(Dir);
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