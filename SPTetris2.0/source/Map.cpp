/* Map class
** Construct a map
**
** Created by Stefan Hagdahl
*/

#include "Map.h"

Map::Map(int width, int height)
{
	mWidth = width;
	mHeight = height;
	mOrigo = Vector2f(0.0f, 0.0f);

	mMap = new MapTile*[mWidth * mHeight];

	for(int i=0;i<mHeight;i++)
	{
		for(int j=0; j<mWidth; j++)
		{
			MapTile *m = new MapTile();
			//m->Block = new Block(0.0f, 0.0f);
			m->tile = new Block(0.0f, 0.0f, "gfx/tile.png");
			float x = ((Block*)m->tile)->getSize().x * j;
			float y = ((Block*)m->tile)->getSize().y * i;
			m->tile->moveX(x);
			m->tile->moveY(y);
			mMap[i*mWidth+j] = m;
		}
	}
	mStart = Vector2f((mWidth * mMap[0]->tile->getSize().x) / 2.0f, mMap[0]->tile->getSize().y * 3);
}

Map::~Map()
{
	for(int i=0;i<(mWidth * mHeight);i++)
	{
		mMap[i]->block = NULL;
		delete mMap[i]->tile;
		delete mMap[i];
	}
	delete mMap;
}

void Map::draw(RenderWindow *window)
{
	for(int i=0; i<(mWidth * mHeight); i++)
	{
		window->draw(*mMap[i]->tile);
	}
}

void Map::drop(TetrisPiece &TPiece)
{
	Block *b0 = TPiece.getBlock0();
	Block *b1 = TPiece.getBlock1();
	Block *b2 = TPiece.getBlock2();
	Block *b3 = TPiece.getBlock3();
	Vector2f size = b0->getSize();
	Vector2f pos0 = b0->getPosition();
	Vector2f pos1 = b1->getPosition();
	Vector2f pos2 = b2->getPosition();
	Vector2f pos3 = b3->getPosition();

	//mMap[heightPos * width + widthPos]
	mMap[(int)((pos0.y / size.y) * mWidth + (pos0.x / size.x))]->block = b0;
	mMap[(int)((pos1.y / size.y) * mWidth + (pos1.x / size.x))]->block = b1;
	mMap[(int)((pos2.y / size.y) * mWidth + (pos2.x / size.x))]->block = b2;
	mMap[(int)((pos3.y / size.y) * mWidth + (pos3.x / size.x))]->block = b3;
}

bool Map::isValidMove(TetrisPiece &TPiece)
{
	Block *b0 = TPiece.getBlock0();
	Vector2f size = b0->getSize();
	float width = mWidth * size.x;
	Vector2f pos0 = b0->getPosition();
	if(pos0.x + size.x > width || pos0.x < mOrigo.x)
		return false;

	Block *b1 = TPiece.getBlock1();
	Vector2f pos1 = b1->getPosition();
	if(pos1.x + size.x > width || pos1.x < mOrigo.x)
		return false;

	Block *b2 = TPiece.getBlock2();
	Vector2f pos2 = b2->getPosition();
	if(pos2.x + size.x > width || pos2.x < mOrigo.x)
		return false;

	Block *b3 = TPiece.getBlock3();
	Vector2f pos3 = b3->getPosition();
	if(pos3.x + size.x > width || pos3.x < mOrigo.x)
		return false;

	return true;
}

Vector2f Map::getStartPos()
{
	return mStart;
}