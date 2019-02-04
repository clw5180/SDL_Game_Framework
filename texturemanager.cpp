//=============================================================================
#include "texturemanager.h"
#include "game.h"
#include "log.h"
#include "filemanager.h"

CTextureManager* CTextureManager::pInstance = 0;
//=============================================================================
std::map<std::string, CTexture*> CTextureManager::TexList;

//=============================================================================
bool CTextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	return AddImage(pRenderer, id, fileName);
}

bool CTextureManager::AddImage(SDL_Renderer* Renderer, std::string ID, std::string Filename)
{
	if (ID == "")
	{
		Log("Bad ID passed");
		return false;
	}

	if (Renderer == NULL)
	{
		Log("Bad SDL renderer passed");
		return false;
	}

	SDL_Surface* TempSurface = IMG_Load(Filename.c_str());
	if (TempSurface == NULL)
	{
		Log("Unable to load image : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}

	SDL_Texture* pTexture;
	// Convert SDL surface to a texture
	if ((pTexture = SDL_CreateTextureFromSurface(Renderer, TempSurface)) == NULL)
	{
		Log("Unable to create SDL Texture : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}

	m_textureMap[ID] = pTexture;

	// Grab dimensions   
	// clw note: SDL_QueryTexture的作用：查询texture的属性
	//SDL_QueryTexture(m_SDLTexture, NULL, NULL, &m_Width, &m_Height);
	//Log("Texture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);

	SDL_FreeSurface(TempSurface);

	//Log("Able to LoadFromImageFile Texture: %s", ID.c_str());
	return true;
}

bool CTextureManager::Init() 
{
	Cleanup();

	SDL_Renderer* m_pRenderer = CGame::Instance()->GetRenderer();
	if(!m_pRenderer) 
		return false;

	//clw note：这里需要根据实际情况修改Folder的名字，如res等
	//          加载Folder内所有文件，并将所有.jpg或.png或.bmp后缀的文件加入TextureList
	std::vector<std::string> Files = CFileManager::GetFilesInFolder("data"); // Relative to CWD

	for(auto Filename : Files) 
	{
        std::string Ext = CFileManager::GetFilenameExt(Filename);
		std::string ID  = CFileManager::GetFilenameWithoutExt(Filename);

        // Skip all non-png files
        if(Ext != "png" && Ext != "jpg" && Ext != "bmp")  //clw modify 20190131：加了jpg和bmp两种类型
			continue;

		//Log("Add CTexture : ID = %s : Filename = %s : Ext = %s", ID.c_str(), Filename.c_str(), Ext.c_str());
		
		AddTexture(m_pRenderer, ID, Filename);
	}

	return true;
}

//-----------------------------------------------------------------------------
void CTextureManager::Cleanup() 
{
	if(TexList.size() <= 0) return;

	for(auto& Iterator : TexList) 
	{
		CTexture* TheTexture = (CTexture*)Iterator.second;

		if(TheTexture) 
		{
			delete TheTexture;
			TheTexture = NULL;
		}
	}

	TexList.clear();
}

//=============================================================================
void CTextureManager::AddTexture(SDL_Renderer* m_pRenderer, std::string ID, std::string Filename) 
{
    if(ID == "") 
		return;

    CTexture* NewTexture = new CTexture();
    if(NewTexture->Load(m_pRenderer, Filename) == false) 
	{
		Log("Unable to Load CTexture: %s", ID.c_str());
		return;
	}

    TexList[ID] = NewTexture;
}

//-----------------------------------------------------------------------------
CTexture* CTextureManager::Get(std::string ID) 
{
	if(TexList.find(ID) == TexList.end()) 
		return NULL;   //clw note：如果TexList找不到这个List，直接返回NULL；

	return TexList[ID];
}

//=============================================================================
void CTextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}

void CTextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer
	*pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
		&destRect, 0, 0, flip);
}
