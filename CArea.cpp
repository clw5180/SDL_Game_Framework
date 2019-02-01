#include "CArea.h"
#include "App.h" //clw modify 20190131

CArea CArea::AreaControl;

CArea::CArea() 
{
	Tex_Tileset = new Texture(); //clw modify 20190131
	AreaSize = 0;
}

bool CArea::OnLoad(const char File[]) 
{
	MapList.clear();

	FILE* FileHandle = fopen(File, "r");

	if (FileHandle == NULL) 
	{
		return false;
	}

	char TilesetFile[255];
	fscanf(FileHandle, "%s\n", TilesetFile);
	std::string strTilesetFile(TilesetFile);

	if (Tex_Tileset == NULL)
		return false;
	if (Tex_Tileset->Load(CApp::GetInstance()->GetRenderer(), strTilesetFile) == false)
	{
		fclose(FileHandle);

		return false;
	}

	fscanf(FileHandle, "%d\n", &AreaSize);

	for (int X = 0; X < AreaSize; X++) 
	{
		for (int Y = 0; Y < AreaSize; Y++) 
		{
			char MapFile[255];

			fscanf(FileHandle, "%s ", MapFile);

			CMap tempMap;
			if (tempMap.OnLoad(MapFile) == false) 
			{
				fclose(FileHandle);

				return false;
			}

			tempMap.Tex_Tileset = Tex_Tileset; //clw note：这里会copy过来，所以只用new这里的Tex_Tileset就可以了。

			MapList.push_back(tempMap);
		}
		fscanf(FileHandle, "\n");
	}

	fclose(FileHandle);

	return true;
}

void CArea::OnRender(int CameraX, int CameraY) 
{
	int MapWidth = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	int FirstID = -CameraX / MapWidth;
	FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);

	for (int i = 0; i < 4; i++)
	{
		int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

		if (ID < 0 || ID >= MapList.size()) continue;

		int X = ((ID % AreaSize) * MapWidth) + CameraX;
		int Y = ((ID / AreaSize) * MapHeight) + CameraY;

		MapList[ID].OnRender(X, Y);
	}
}

void CArea::OnCleanup() 
{
	//if (Surf_Tileset) {
	//	SDL_FreeSurface(Surf_Tileset);
	//}

	MapList.clear();
}