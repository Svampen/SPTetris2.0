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

void ResourceMgr::loadTexture(const string Texture)
{
	Tex *t = new Tex();
	if(!t->mTex.loadFromFile(Texture))
	{
		// Error loading texture
	}
	t->Texture = Texture;
}

bool ResourceMgr::isTextureLoaded(const string Texture)
{
	return false;
}