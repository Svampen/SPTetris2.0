#ifndef RESOURCEMGR_H
#define RESOURCEMGR_H

#include "Tetris.h"
#include "List.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class ResourceMgr
{
public:
	ResourceMgr();
	~ResourceMgr();

	Texture& getTexture(const string Texture);

	struct Tex
	{
		// The actual texture from SFML
		Texture mTex;
		// The name of the texture
		string Texture;
	};

private:

	List<Tex> *mTexList;
};

extern ResourceMgr *RMgr;
#endif