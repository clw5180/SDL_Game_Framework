#ifndef _CMAP_H_
#define _CMAP_H_

#include <SDL.h>
#include <vector>

#include "CTile.h"
//#include "CSurface.h"
#include "Texture.h"

class CMap 
{
public:
	//SDL_Surface* Surf_Tileset;
	Texture* Tex_Tileset;

private:
	std::vector<CTile> TileList;

public:
	CMap();

public:
	bool OnLoad(char* File);

	void OnRender(int MapX, int MapY);
};

#endif