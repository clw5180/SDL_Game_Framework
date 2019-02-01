#include "CMap.h"

CMap::CMap() 
{
	//Surf_Tileset = NULL;
	Tex_Tileset = NULL;
}

bool CMap::OnLoad(char* File) 
{
	TileList.clear();

	FILE* FileHandle = fopen(File, "r");

	if (FileHandle == NULL) {
		return false;
	}

	for (int Y = 0; Y < MAP_HEIGHT; Y++) 
	{
		for (int X = 0; X < MAP_WIDTH; X++) 
		{
			CTile tempTile;

			fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

			TileList.push_back(tempTile);
		}
		fscanf(FileHandle, "\n");
	}

	fclose(FileHandle);

	return true;
}

void CMap::OnRender(int MapX, int MapY) 
{
	//if (Surf_Tileset == NULL) return;
	if (Tex_Tileset == NULL) 
		return;

	int TilesetWidth = Tex_Tileset->GetWidth() / TILE_SIZE;
	int TilesetHeight = Tex_Tileset->GetHeight() / TILE_SIZE;

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].TypeID == TILE_TYPE_NONE) {
				ID++;
				continue;
			}

			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);

			int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
			int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

			Tex_Tileset->RenderEx(tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

			//CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

			ID++;
		}
	}
}