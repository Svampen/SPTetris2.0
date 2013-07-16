/* Map class
** Construct a map
**
** Created by Stefan Hagdahl
*/

#include "Map.h"

Map::Map(int width, int height, int startX, int startY)
{
	mWidth = width;
	mHeight = height;
	mOrigo = Vector2f(startX, startY);

	mMap = new MapTile*[mWidth * mHeight];

	for(int i=0;i<mHeight;i++)
	{
		for(int j=0; j<mWidth; j++)
		{
			MapTile *m = new MapTile();
			m->block = NULL;
			m->tile = new Block(0.0f, 0.0f, "gfx/tile.png");
			float x = startX + ((Block*)m->tile)->getSize().x * j;
			float y = startY + ((Block*)m->tile)->getSize().y * i;
			m->tile->moveX(x);
			m->tile->moveY(y);
			mMap[i*mWidth+j] = m;
		}
	}
	mStart = Vector2f((startX + (mWidth * mMap[0]->tile->getSize().x) / 2.0f), startY + (mMap[0]->tile->getSize().y * 3));
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
	mMap[(int)(((pos0.y - mOrigo.y) / size.y) * mWidth + ((pos0.x - mOrigo.x) / size.x))]->block = b0;
	mMap[(int)(((pos1.y - mOrigo.y) / size.y) * mWidth + ((pos1.x - mOrigo.x) / size.x))]->block = b1;
	mMap[(int)(((pos2.y - mOrigo.y) / size.y) * mWidth + ((pos2.x - mOrigo.x) / size.x))]->block = b2;
	mMap[(int)(((pos3.y - mOrigo.y) / size.y) * mWidth + ((pos3.x - mOrigo.x) / size.x))]->block = b3;
}

bool Map::isValidMove(TetrisPiece &TPiece)
{
	Block *b0 = TPiece.getBlock0();
	Vector2f size = b0->getSize();
	float width = mOrigo.x + mWidth * size.x;
	float height = mOrigo.y + mHeight * size.y;
	Vector2f pos0 = b0->getPosition();
	if((pos0.x + size.x > width || pos0.x < mOrigo.x) || 
		(pos0.y + size.y > height))
		return false;

	Block *b1 = TPiece.getBlock1();
	Vector2f pos1 = b1->getPosition();
	if((pos1.x + size.x > width || pos1.x < mOrigo.x) || 
		(pos1.y + size.y > height))
		return false;

	Block *b2 = TPiece.getBlock2();
	Vector2f pos2 = b2->getPosition();
	if((pos2.x + size.x > width || pos2.x < mOrigo.x) || 
		(pos2.y + size.y > height))
		return false;

	Block *b3 = TPiece.getBlock3();
	Vector2f pos3 = b3->getPosition();
	if((pos3.x + size.x > width || pos3.x < mOrigo.x) || 
		(pos3.y + size.y > height))
		return false;

	return true;
}

void Map::syncPiece(TetrisPiece &TPiece)
{
	Block *b0 = TPiece.getBlock0();
	Vector2f size = b0->getSize();
	int i = (int)((b0->getPosition().y - mOrigo.y) / size.y);
	b0->setPos(b0->getPosition().x, mOrigo.y + i * size.y);

	Block *b1 = TPiece.getBlock1();
	i = (int)((b1->getPosition().y - mOrigo.y) / size.y);
	b1->setPos(b1->getPosition().x, mOrigo.y + i * size.y);

	Block *b2 = TPiece.getBlock2();
	i = (int)((b2->getPosition().y - mOrigo.y) / size.y);
	b2->setPos(b2->getPosition().x, mOrigo.y + i * size.y);

	Block *b3 = TPiece.getBlock3();
	i = (int)((b3->getPosition().y - mOrigo.y) / size.y);
	b3->setPos(b3->getPosition().x, mOrigo.y + i * size.y);
}

int* Map::checkCompleteRow(TetrisPiece &TPiece)
{
	Vector2f pos0 = TPiece.getBlock0()->getPosition();
	Vector2f pos1 = TPiece.getBlock1()->getPosition();
	Vector2f pos2 = TPiece.getBlock2()->getPosition();
	Vector2f pos3 = TPiece.getBlock3()->getPosition();

	Vector2f size = TPiece.getBlock0()->getSize();

	int row0 = (int)((pos0.y - mOrigo.y) / size.y);
	int row1 = (int)((pos1.y - mOrigo.y) / size.y);
	int row2 = (int)((pos2.y - mOrigo.y) / size.y);
	int row3 = (int)((pos3.y - mOrigo.y) / size.y);

	int *rows = new int[4];

	rows[0] = rowComplete(row0);
	if(row1 == row0)
		rows[1] = -1;
	else
		rows[1] = rowComplete(row1);
	if(row2 == row1 || row2 == row0)
		rows[2] = -1;
	else
		rows[2] = rowComplete(row2);
	if(row3 == row2 || row3 == row1 || row3 == row0)
		rows[3] = -1;
	else
		rows[3] = rowComplete(row3);

	return rows;
}

int Map::rowComplete(int row)
{
	for(int i=0; i<mWidth; i++)
	{
		if(mMap[row * mWidth + i]->block == NULL)
			return -1;
	}
	return row;
}

Block** Map::clearRow(int row)
{
	Block** blist = new Block*[mWidth];
	for(int i=0; i<mWidth; i++)
	{
		blist[i] = mMap[row * mWidth + i]->block;
		mMap[row * mWidth + i]->block = NULL;
	}
	return blist;
}

void Map::clearMap()
{
	for(int i=0;i<(mWidth * mHeight);i++)
	{
		mMap[i]->block = NULL;
	}
}

Vector2f Map::getStartPos()
{
	return mStart;
}

void Map::moveBlocks(int startRow)
{
	for(int i=startRow; i>=0; i--)
	{
		for(int j=mWidth-1; j>=0; j--)
		{
			if(mMap[i * mWidth + j]->block != NULL)
			{
				mMap[i * mWidth + j]->block->move(Block::DOWN);
				mMap[(i + 1) * mWidth + j]->block = mMap[i * mWidth + j]->block;
				mMap[i * mWidth + j]->block = NULL;
			}
		}
	}
}