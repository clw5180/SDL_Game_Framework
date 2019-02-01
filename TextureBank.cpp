//=============================================================================
#include "TextureBank.h"
#include "App.h"
#include "Log.h"
#include "FileManager.h"
//=============================================================================
std::map<std::string, Texture*> TextureBank::TexList;

//=============================================================================
bool TextureBank::Init() 
{
	Cleanup();

	SDL_Renderer* Renderer = CApp::GetInstance()->GetRenderer();
	if(!Renderer) 
		return false;

	//clw note：这里需要根据实际情况修改Folder的名字，如res等
	//          加载Folder内所有文件，并将所有.jpg或.png或.bmp后缀的文件加入TextureList
	std::vector<std::string> Files = FileManager::GetFilesInFolder("data"); // Relative to CWD

	for(auto Filename : Files) 
	{
        std::string Ext = FileManager::GetFilenameExt(Filename);
		std::string ID  = FileManager::GetFilenameWithoutExt(Filename);

        // Skip all non-png files
        if(Ext != "png" && Ext != "jpg" && Ext != "bmp")  //clw modify 20190131：加了jpg和bmp两种类型
			continue;

		//Log("Add Texture : ID = %s : Filename = %s : Ext = %s", ID.c_str(), Filename.c_str(), Ext.c_str());
		
		AddTexture(Renderer, ID, Filename);
	}

	return true;
}

//-----------------------------------------------------------------------------
void TextureBank::Cleanup() 
{
	if(TexList.size() <= 0) return;

	for(auto& Iterator : TexList) 
	{
		Texture* TheTexture = (Texture*)Iterator.second;

		if(TheTexture) 
		{
			delete TheTexture;
			TheTexture = NULL;
		}
	}

	TexList.clear();
}

//=============================================================================
void TextureBank::AddTexture(SDL_Renderer* Renderer, std::string ID, std::string Filename) 
{
    if(ID == "") 
		return;

    Texture* NewTexture = new Texture();
    if(NewTexture->Load(Renderer, Filename) == false) 
	{
		Log("Unable to Load Texture: %s", ID.c_str());
		return;
	}

    TexList[ID] = NewTexture;
}

//-----------------------------------------------------------------------------
Texture* TextureBank::Get(std::string ID) 
{
	if(TexList.find(ID) == TexList.end()) 
		return NULL;   //clw note：如果TexList找不到这个List，直接返回NULL；

	return TexList[ID];
}

//=============================================================================
