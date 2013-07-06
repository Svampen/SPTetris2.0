/* Block class
** Basic block to construct a tetris shape
**
** Created by Stefan Hagdahl
*/

#include "Block.h"

Block::Block()
{
	if(!mTex.loadFromFile("gfx/cyan.png"))
	{
		//error
	}
	setTexture(mTex);
	FloatRect r = getGlobalBounds();
	Vector2f size(26.0f, 26.0f);
	mScaleX = size.x / r.width;
	mScaleY = size.y / r.height;
	mX = 0.0f;
	mY = 0.0f;
	mOldX = 0.0f;
	mOldY = 0.0f;
	// Should be determined by size of resolution
	Sprite::scale(mScaleX, mScaleY);
	mCenter = false;
	mSize = Vector2f(getGlobalBounds().width, getGlobalBounds().height);
}

Block::Block(float X, float Y) 
{
	if(!mTex.loadFromFile("gfx/cyan.png"))
	{
		//error
	}
	setTexture(mTex);
	FloatRect r = getGlobalBounds();
	Vector2f size(26.0f, 26.0f);
	mScaleX = size.x / r.width;
	mScaleY = size.y / r.height;
	mX = X;
	mY = Y;
	mOldX = X;
	mOldY = Y;
	// Should be determined by size of resolution
	Sprite::scale(mScaleX, mScaleY);
	mCenter = false;
	mSize = Vector2f(getGlobalBounds().width, getGlobalBounds().height);

}

Block::~Block()
{
}
/* Set a absolute position, used for initial position of block
*/
void Block::setPos(float X, float Y)
{
	mOldX = X;
	mOldY = Y;
	mX = X;
	mY = Y;
	Sprite::setPosition(mX, mY);
}
void Block::move(float X, float Y)
{
	mOldX = mX;
	mOldY = mY;
	mX = X;
	mY = Y;
	Sprite::setPosition(mX, mY);
}

void Block::moveX(float X)
{
	mOldX = mX;
	mOldY = mY;
	mX += X;
	Sprite::setPosition(mX, mY);
}

void Block::moveY(float Y)
{
	mOldX = mX;
	mOldY = mY;
	mY += Y;
	Sprite::setPosition(mX, mY);
}

void Block::onLostDevice()
{

}

void Block::onResetDevice()
{

}

void Block::draw()
{

}

void Block::setOldPos()
{
	mX = mOldX;
	mY = mOldY;
	Sprite::setPosition(mX, mY);
}

Vector2f Block::getSize()
{
	return mSize;
}