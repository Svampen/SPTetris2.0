#ifndef PIECEBUILDER_H
#define PIECEBUILDER_H
#include "List.h"
#include "Block.h"
#include "TetrisPiece.h"
#include "IPiece.h"
#include "LPiece.h"
#include "SPiece.h"
#include "OPiece.h"
#include "JPiece.h"
#include "TPiece.h"
#include "ZPiece.h"

class PieceBuilder
{
public:
	struct BlockPool
	{
		Block *mBlock;
		// free specific if it can by allocated by a piece or not
		// If not then it is either used by a piece or still on the board
		bool free;
		// usedbypiece specific if it used by a piece at the moment
		// if so then PieceBuilder should let the piece control it.
		bool usedbypiece;
	};

	enum Piece
	{
		I = 0,
		J = 1,
		L = 2,
		O = 3,
		S = 4,
		T = 5,
		Z = 6
	};
	PieceBuilder();
	~PieceBuilder();

	TetrisPiece& addPiece(Piece piece, float X, float Y);
	void delPiece(TetrisPiece *TPiece);
	void draw(RenderWindow *window);
	bool isValidMove(TetrisPiece &TPiece);
	void freeBlock(Block *block);
	void onLostDevice();
	void onResetDevice();

private:
	Block& takeFreeBlock();
	void allocateBlocks(int NrOfBlocks);
	List<BlockPool> *mBlockPool;
};

#endif