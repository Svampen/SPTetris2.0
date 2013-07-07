#ifndef TETRISPIECE_H
#define TETRISPIECE_H
#include "List.h"
#include "Block.h"

class TetrisPiece
{
public:
	
	TetrisPiece();
	~TetrisPiece();
	// Virtual function that all inherited classes needs to implement
	// Rotate blocks clockwise
	virtual void rotate()
	{
	}
	virtual void onLostDevice()
	{
	}
	virtual void onResetDevice()
	{
	}
	virtual void draw(RenderWindow *Window)
	{
	}
	Block* getBlock0()
	{
		return mBlock0;
	}
	Block* getBlock1()
	{
		return mBlock1;
	}
	Block* getBlock2()
	{
		return mBlock2;
	}
	Block* getBlock3()
	{
		return mBlock3;
	}
	void move(Block::DIR Dir);
	void fall(float dt);
	void revertMove();
	void setOldRotationStage();
protected:
	Block *mBlock0;
	Block *mBlock1;
	Block *mBlock2;
	Block *mBlock3;
	int mRotationStage;
	int mOldRotationStage;
	float mFallSpeedPerFps;
};

#endif