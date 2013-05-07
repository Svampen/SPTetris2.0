#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Block : public Sprite
{
public:

	Block();
	Block(float X, float Y);
	~Block();
	
	void setPos(float X, float Y);
	void move(float X, float Y);
	void moveX(float X);
	void moveY(float Y);
	void draw();
	void onResetDevice();
	void onLostDevice();
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