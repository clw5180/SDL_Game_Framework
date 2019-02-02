#ifndef __MAP_H__
#define __MAP_H__

#include <SDL.h>
#include <vector>

#include "tile.h"
//#include "CSurface.h"
#include "texture.h"

class CMap 
{
public:
	CMap();

	void SetTextureTileset(CTexture* Tileset) { Tex_Tileset = Tileset; }

	bool OnLoad(char* File);

	void OnRender(int MapX, int MapY);

private:
	std::vector<CTile> TileList;

	//SDL_Surface* Surf_Tileset;
	CTexture* Tex_Tileset;
};

#endif