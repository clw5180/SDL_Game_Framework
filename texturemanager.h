#ifndef __TEXTUREBANK_H__
#define __TEXTUREBANK_H__

#include <map>
#include <string>
#include <vector>
#include "texture.h"

class CTextureManager 
{
public:
	static bool Init();

	static void Cleanup();

	static CTexture* Get(std::string ID);

	static CTextureManager* Instance()
	{
		if (pInstance == NULL)
		{
			pInstance = new CTextureManager();
		}
		return pInstance;
	}

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	// load image and text    
	bool AddImage(SDL_Renderer* Renderer, std::string ID, std::string Filename);//加载图片到TextureManager中  

	void clearFromTextureMap(std::string id);

	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer*
		pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//=========================================================
	//Get方法声明
	//=========================================================
	SDL_Texture* GetTextureFromList(std::string ID)
	{
		if (m_textureMap.find(ID) == m_textureMap.end())
			return 0;
		return m_textureMap[ID];
	}

	static void AddTexture(SDL_Renderer* m_pRenderer, std::string ID, std::string Filename);

private:
	
	static std::map<std::string, CTexture*> TexList;

	//=========================================================
	//子程式声明
	//=========================================================
	//void free();  ////GetTextureFromList rid of preexisting texture

	//=========================================================
	//数据成员声明
	//=========================================================
	std::map<std::string, SDL_Texture*> m_textureMap;

	static CTextureManager* pInstance;

	//TTF_Font* m_pFont = NULL;
};

typedef CTextureManager TheTextureManager;

#endif
