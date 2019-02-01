#ifndef _CAREA_H_
#define _CAREA_H_

#include "CMap.h"

class CArea {
public:
	static CArea            AreaControl;

public:
	std::vector<CMap>       MapList;

private:
	int                     AreaSize;

	//SDL_Surface*        Surf_Tileset;
	Texture* Tex_Tileset;

public:
	CArea();

	bool    OnLoad(const char File[]);

	void    OnRender(int CameraX, int CameraY); //clw note£∫¥˝ÕÍ£¨µ»camera¿‡£ª

	void    OnCleanup();
};

#endif