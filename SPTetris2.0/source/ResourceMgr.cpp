#include "ResourceMgr.h"

ResourceMgr::ResourceMgr()
{
	mTexList = new List<Tex>();
}

ResourceMgr::~ResourceMgr()
{
	for(int i=0; i<mTexList->getSize(); i++)
	{
		mTexList->deleteElementAt(i);
	}
	delete mTexList;
}

Texture ResourceMgr::getTexture(const string Texture)
{
	for(int i=0; i<mTexList->getSize(); i++)
	{
		if(mTexList->getAt(i)->Texture == Texture)
			return mTexList->getAt(i)->mTex;
	}

	Tex *t = new Tex();
	if(t->mTex.loadFromFile(Texture))
	{
		t->Texture = Texture;
		mTexList->addFirst(t);
		return t->mTex;
	}
	// Error loading/finding texture
}