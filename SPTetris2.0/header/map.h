#ifndef MAP_H
#define MAP_H

#include "Block.h"
#include "TetrisPiece.h"

class Map
{
public:
	Map(int width, int height, int startX, int startY);
	~Map();

	void draw(RenderWindow *window);
	void drop(TetrisPiece &TPiece);
	bool isValidMove(TetrisPiece &TPiece);
	void syncPiece(TetrisPiece &TPiece);
	int* checkCompleteRow(TetrisPiece &TPiece);
	Block** clearRow(int row);
	void clearMap();
	void moveBlocks(int startRow);
	Vector2f getStartPos();
	int getWidth()
	{
		return mWidth;
	}
	int getHeight()
	{
		return mHeight;
	}

private:
	int rowComplete(int row);

	struct MapTile
	{
		// Drawing background
		Block *tile;
		// Containing the block for a tetris piece that isn't active anymore
		Block *block;
	};

	MapTile **mMap;
	Vector2f mOrigo; 
	int mWidth;
	int mHeight;
	int mStartX;
	int mStartY;
	Vector2f mStart;

};
#endif