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

	void loadTexture(const string Texture);
	bool isTextureLoaded(const string Texture);
	Texture getTexture(const string Texture);

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
#endif