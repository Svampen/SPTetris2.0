/* Block class
** Basic block to construct a tetris shape
**
** Created by Stefan Hagdahl
*/

#include "Block.h"

Block::Block()
{
	initBlock(0.0f, 0.0f, "gfx/cyan.png");
}

Block::Block(float X, float Y)
{
	initBlock(X, Y, "gfx/cyan.png");
}

Block::Block(float X, float Y, const std::string Texture) 
{
	initBlock(X, Y, Texture);
}
Block::~Block()
{
}

void Block::initBlock(float X, float Y, const std::string Texture)
{
	setTexture(RMgr->getTexture(Texture));
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

void Block::move(DIR Dir)
{
	float X = 0.0f;
	float Y = 0.0f;
	switch(Dir)
	{
	case LEFT:
		X -= (mSize.x * 1);
		moveX(X);
		break;
	case RIGHT:
		X += mSize.x * 1;
		moveX(X);
		break;
	case DOWN:
		Y += mSize.y * 1;
		moveY(Y);
	}
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