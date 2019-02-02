#ifndef __AREA_H__
#define __AREA_H__

#include "map.h"

class CArea 
{
public:
	CArea();

	static CArea& GetAreaControl() { return AreaControl; }

	bool    OnLoad(const char File[]);

	void    OnRender(int CameraX, int CameraY); //clw note�����꣬��camera�ࣻ

	void    OnCleanup();

private:
	int                     AreaSize;

	//SDL_Surface*          Surf_Tileset;
	CTexture*               Tex_Tileset;

	static CArea            AreaControl;

	std::vector<CMap>       MapList;
};

#endif