#ifndef __AREA_H__
#define __AREA_H__

#include "map.h"

class CArea 
{
public:
	CArea();

	static CArea& GetAreaControl() { return AreaControl; }

	bool    OnLoad(const char File[]);

	void    OnRender(int CameraX, int CameraY); //clw note£∫¥˝ÕÍ£¨µ»camera¿‡£ª

	void    OnCleanup();

private:
	int                     AreaSize;

	//SDL_Surface*          Surf_Tileset;
	SDL_Texture*            m_textureTileset;   //clw modify 20190205
	//CTexture*               Tex_Tileset;

	static CArea            AreaControl;

	std::vector<CMap>       MapList;
};

#endif