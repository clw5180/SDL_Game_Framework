#include "area.h"
#include "game.h" //clw modify 20190131
#include "log.h"

CArea CArea::AreaControl;

CArea::CArea() 
{
	//Tex_Tileset = new CTexture(); //clw modify 20190131
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
	fscanf(FileHandle, "%s\n", TilesetFile);  //clw note：TilesetFile形如 ./tilesets/1.png

	/*********************************************/
	//clw note：注意char*和string之间的转换：
	//（1）char*类型转为str类型例子：
	// std::string strTilesetFile(TilesetFile); 
	//（2）str转char*类型例子：
	// IMG_Load(strTilesetFile.c_str());
	/*********************************************/

	SDL_Renderer* m_pRenderer = CGame::Instance()->GetRenderer();
	if (m_pRenderer == NULL)
	{
		Log("Bad SDL renderer passed");
		fclose(FileHandle);
		return false;
	}

	SDL_Surface* TempSurface = IMG_Load(TilesetFile);//必须要有libpng16-16.dll这个dll，否则加载.png会失败！
	//如果是.jpg需要libjpeg-9.dll

	if (TempSurface == NULL)
	{
		Log("Unable to load image : %s : %s", TilesetFile, IMG_GetError());
		fclose(FileHandle);
		return false;
	}

	//Color key image
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0xFF, 0, 0xFF));

	// Convert SDL surface to a texture
	if ((m_textureTileset = SDL_CreateTextureFromSurface(m_pRenderer, TempSurface)) == NULL)
	{
		Log("Unable to create SDL CTexture : %s : %s", TilesetFile, IMG_GetError());
		fclose(FileHandle);
		return false;
	}

	// Grab dimensions
	//SDL_QueryTexture(m_textureTileset, NULL, NULL, &Width, &Height);  //clw note：这个需要的时候再查询就行，不用提前查然后存起来

	SDL_FreeSurface(TempSurface);

	/*
	if (Tex_Tileset->Load(CGame::Instance()->GetRenderer(), strTilesetFile) == false)
	if(CTextureManager::Instance()->AddImage(CGame::Instance()->GetRenderer(), "map" ,strTilesetFile) == false)
	*/
	
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

			tempMap.SetTextureTileset(m_textureTileset); //clw note：这里会copy过来，所以只用new这里的Tex_Tileset就可以了。

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

	int FirstID = -CameraX / MapWidth; //比如-700 / 640 = 1
	FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize); //clw note:Areasize是从1.area文件中传进来的，比如3*3的maps，则Areasize=3；所以FirstID=1+3=4

	for (int i = 0; i < 4; i++)
	{
		int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

		if (ID < 0 || ID >= MapList.size()) 
			continue;

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