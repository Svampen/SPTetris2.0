/* Piece Builder class
**
** Created by Stefan Hagdahl
*/
#include "PieceBuilder.h"

PieceBuilder::PieceBuilder()
{
	mBlockPool = new List<BlockPool>();
	// Allocate blocks
	allocateBlocks(300);
}

PieceBuilder::~PieceBuilder()
{
	for(int i=0; i<mBlockPool->getSize(); i++)
	{
		delete mBlockPool->getAt(i)->mBlock;
		mBlockPool->deleteElementAt(i);
	}
	delete mBlockPool;
}

TetrisPiece& PieceBuilder::addPiece(Piece piece, float X, float Y)
{
	// grab 4 free blocks
	Block *b1 = &takeFreeBlock();
	Block *b2 = &takeFreeBlock();
	Block *b3 = &takeFreeBlock();
	Block *b4 = &takeFreeBlock();
	TetrisPiece *p;
	switch(piece)
	{
	case I:
		p = new IPiece(X, Y, b1, b2, b3, b4);
		break;
	case J:
		p = new JPiece(X, Y, b1, b2, b3, b4);
		break;
	case L:
		p = new LPiece(X, Y, b1, b2, b3, b4);
		break;
	case O:
		p = new OPiece(X, Y, b1, b2, b3, b4);
		break;
	case S:
		p = new SPiece(X, Y, b1, b2, b3, b4);
		break;
	case T:
		p = new TPiece(X, Y, b1, b2, b3, b4);
		break;
	case Z:
		p = new ZPiece(X, Y, b1, b2, b3, b4);
		break;
	}
	return *p;
}

Block& PieceBuilder::takeFreeBlock()
{
	for(int i=0; i<mBlockPool->getSize(); i++)
	{
		if(mBlockPool->getAt(i)->free)
		{
			mBlockPool->getAt(i)->free = false;
			mBlockPool->getAt(i)->usedbypiece = true;
			return *mBlockPool->getAt(i)->mBlock;
		}
	}
	allocateBlocks(20);
	return takeFreeBlock();
}

void PieceBuilder::allocateBlocks(int NrOfBlocks)
{

	for(int i=0; i<NrOfBlocks; i++)
	{
		BlockPool *p = new BlockPool();
		Block *b = new Block(0.0f, 0.0f);
		p->mBlock = b;
		p->free = true;
		p->usedbypiece = false;
		mBlockPool->addFirst(p);
	}
}

void PieceBuilder::delPiece(TetrisPiece *TPiece)
{
	// free the blocks from being used by Piece
	for(int i=0; i<mBlockPool->getSize(); i++)
	{
		if(mBlockPool->getAt(i)->mBlock == TPiece->getBlock0())
		{
			mBlockPool->getAt(i)->usedbypiece = false;
		}
		else if(mBlockPool->getAt(i)->mBlock == TPiece->getBlock1())
		{
			mBlockPool->getAt(i)->usedbypiece = false;
		}
		else if(mBlockPool->getAt(i)->mBlock == TPiece->getBlock2())
		{
			mBlockPool->getAt(i)->usedbypiece = false;
		}
		else if(mBlockPool->getAt(i)->mBlock == TPiece->getBlock3())
		{
			mBlockPool->getAt(i)->usedbypiece = false;
		}
	}
	delete TPiece;
}

void PieceBuilder::draw(RenderWindow *window)
{
	for(int i=0; i<mBlockPool->getSize(); i++)
	{
		BlockPool *bp = mBlockPool->getAt(i);
		if(!bp->free && !bp->usedbypiece)
		{
			window->draw(*bp->mBlock);
		}
	}
}

bool PieceBuilder::isValidMove(TetrisPiece &TPiece)
{
	FloatRect r0 = TPiece.getBlock0()->getGlobalBounds();
	FloatRect r1 = TPiece.getBlock1()->getGlobalBounds();
	FloatRect r2 = TPiece.getBlock2()->getGlobalBounds();
	FloatRect r3 = TPiece.getBlock3()->getGlobalBounds();
	for(int i=0; i<mBlockPool->getSize(); i++)
	{
		BlockPool *bp = mBlockPool->getAt(i);
		// Only nessary to check collision against
		// blocks that are not free and not currently
		// used by TetrisPieces
		if(!bp->free && !bp->usedbypiece)
		{
			FloatRect r = bp->mBlock->getGlobalBounds();
			if(r.intersects(r0))
				return false;
			if(r.intersects(r1))
				return false;
			if(r.intersects(r2))
				return false;
			if(r.intersects(r3))
				return false;
		}
	}
	return true;
}
void PieceBuilder::freeBlocks(Block **blist, int length)
{
	for(int i=0; i<mBlockPool->getSize(); i++)
	{
		BlockPool *bp = mBlockPool->getAt(i);
		for(int j=0; j<length; j++)
		{
			if(bp->mBlock == blist[j])
			{
				bp->free = true;
				break;
			}
		}
	}
}
void PieceBuilder::freeBlock(Block *block)
{
	for(int i=0; i<mBlockPool->getSize(); i++)
	{
		BlockPool *bp = mBlockPool->getAt(i);
		if(bp->mBlock == block)
		{
			bp->free = true;
			break;
		}
	}
}

void PieceBuilder::onLostDevice()
{
	for(int i=0; i<mBlockPool->getSize(); i++)
	{
		BlockPool *bp = mBlockPool->getAt(i);
		bp->mBlock->onLostDevice();
	}
}

void PieceBuilder::onResetDevice()
{
	for(int i=0; i<mBlockPool->getSize(); i++)
	{
		BlockPool *bp = mBlockPool->getAt(i);
		bp->mBlock->onResetDevice();
	}
}