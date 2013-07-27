#ifndef BLOCK_H
#define BLOCK_H

#include "ResourceMgr.h"
#include "Tetris.h"

class Block : public Sprite
{
public:
	enum DIR
	{
		LEFT = 0,
		RIGHT = 1,
		DOWN = 2
	};

	Block();
	Block(float X, float Y, const std::string Texture);
	Block(float X, float Y);
	~Block();
	
	void setPos(float X, float Y);
	void move(float X, float Y);
	void move(DIR Dir);
	void moveX(float X);
	void moveY(float Y);
	void draw();
	float getX()
	{
		return mX;
	}
	float getY()
	{
		return mY;
	}
	bool isCenter()
	{
		mCenter;
	}
	void setCenter(bool Center)
	{
		mCenter = Center;
	}
	void setOldPos();

	Vector2f getSize();

private:

	void initBlock(float X, float Y, const std::string Texture);

	int mType;
	Texture mTex;
	float mScaleX;
	float mScaleY;
	Vector2f mSize;

	float mX, mOldX;
	float mY, mOldY;

	bool mCenter;
};

#endif