#ifndef __TILE_H__
#define __TILE_H__

#include "define.h"

enum 
{
	TILE_TYPE_NONE = 0,
	TILE_TYPE_NORMAL,
	TILE_TYPE_BLOCK
};

class CTile 
{
public:
	CTile();

	int& GetTileID() { return TileID; }
	int& GetTypeID() { return TypeID; }

private:
	int     TileID;
	int     TypeID;
};

#endif