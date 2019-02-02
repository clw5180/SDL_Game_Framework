//=============================================================================
#include "texturebank.h"
#include "game.h"
#include "log.h"
#include "filemanager.h"
//=============================================================================
std::map<std::string, CTexture*> CTextureBank::TexList;

//=============================================================================
bool CTextureBank::Init() 
{
	Cleanup();

	SDL_Renderer* Renderer = CGame::GetInstance()->GetRenderer();
	if(!Renderer) 
		return false;

	//clw note��������Ҫ����ʵ������޸�Folder�����֣���res��
	//          ����Folder�������ļ�����������.jpg��.png��.bmp��׺���ļ�����TextureList
	std::vector<std::string> Files = CFileManager::GetFilesInFolder("data"); // Relative to CWD

	for(auto Filename : Files) 
	{
        std::string Ext = CFileManager::GetFilenameExt(Filename);
		std::string ID  = CFileManager::GetFilenameWithoutExt(Filename);

        // Skip all non-png files
        if(Ext != "png" && Ext != "jpg" && Ext != "bmp")  //clw modify 20190131������jpg��bmp��������
			continue;

		//Log("Add CTexture : ID = %s : Filename = %s : Ext = %s", ID.c_str(), Filename.c_str(), Ext.c_str());
		
		AddTexture(Renderer, ID, Filename);
	}

	return true;
}

//-----------------------------------------------------------------------------
void CTextureBank::Cleanup() 
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
void CTextureBank::AddTexture(SDL_Renderer* Renderer, std::string ID, std::string Filename) 
{
    if(ID == "") 
		return;

    CTexture* NewTexture = new CTexture();
    if(NewTexture->Load(Renderer, Filename) == false) 
	{
		Log("Unable to Load CTexture: %s", ID.c_str());
		return;
	}

    TexList[ID] = NewTexture;
}

//-----------------------------------------------------------------------------
CTexture* CTextureBank::Get(std::string ID) 
{
	if(TexList.find(ID) == TexList.end()) 
		return NULL;   //clw note�����TexList�Ҳ������List��ֱ�ӷ���NULL��

	return TexList[ID];
}

//=============================================================================
