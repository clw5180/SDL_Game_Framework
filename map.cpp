#include "map.h"
#include "game.h"

CMap::CMap() 
{
	//Surf_Tileset = NULL;
	m_textureTileset = NULL;
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

			fscanf(FileHandle, "%d:%d ", &tempTile.GetTileID(), &tempTile.GetTypeID());

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
	if (m_textureTileset == NULL)
		return;


	// Grab dimensions
	int width;
	int height;
    SDL_QueryTexture(m_textureTileset, NULL, NULL, &width, &height);  //clw note�������Ҫ��ʱ���ٲ�ѯ���У�������ǰ��Ȼ�������

	int TilesetWidth = width / TILE_SIZE;
	int TilesetHeight = height / TILE_SIZE;

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) 
	{
		for (int X = 0; X < MAP_WIDTH; X++) 
		{
			if (TileList[ID].GetTypeID() == TILE_TYPE_NONE) 
			{
				ID++;
				continue;
			}

			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);

			int TilesetX = (TileList[ID].GetTileID() % TilesetWidth) * TILE_SIZE;
			int TilesetY = (TileList[ID].GetTileID() / TilesetWidth) * TILE_SIZE;


			SDL_Rect Source = { TilesetX, TilesetY, TILE_SIZE, TILE_SIZE };
			SDL_Rect Destination;
			Destination.x = tX;
			Destination.y = tY;
			Destination.w = TILE_SIZE;  //clw note��ע�⣺����ط�����ø�ֵ���������Ĭ��ֵ0�������Ļ�Ͼ�ʲôҲû�У�����
			Destination.h = TILE_SIZE;
			SDL_RenderCopyEx(CGame::Instance()->GetRenderer(), m_textureTileset, &Source, &Destination, 0, 0, SDL_FLIP_NONE);


			//Tex_Tileset->RenderEx(tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

			//CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

			ID++;
		}
	}
}