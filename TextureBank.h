#ifndef __TEXTUREBANK_H__
#define __TEXTUREBANK_H__

#include <map>
#include <string>
#include <vector>
#include "texture.h"

class CTextureBank 
{
public:
	static bool Init();

	static void Cleanup();

	static CTexture* Get(std::string ID);

	static CTextureBank* GetInstance();

private:
	static void AddTexture(SDL_Renderer* Renderer, std::string ID, std::string Filename);

	static std::map<std::string, CTexture*> TexList;
};

#endif
