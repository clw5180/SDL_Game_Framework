//==============================================================================
#include "App.h"
#include "Log.h"

#include <vector>
#include "FileManager.h"

#include "Define.h"

#include "CArea.h"
#include "CCamera.h"

//==============================================================================
CApp* CApp::s_pInstance = NULL;

//------------------------------------------------------------------------------
void CApp::OnEvent(SDL_Event* Event) 
{
}

//------------------------------------------------------------------------------
bool CApp::Init() 
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		Log("Unable to Init SDL: %s", SDL_GetError());
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) 
	{
		Log("Unable to Init hinting: %s", SDL_GetError());
	}

	if ((Window = SDL_CreateWindow("My SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN)) == NULL) 
	{
		Log("Unable to create SDL Window: %s", SDL_GetError());
		return false;
	}

	PrimarySurface = SDL_GetWindowSurface(Window);

	if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL) 
	{
	    Log("Unable to create renderer");
	    return false;
	}

	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);  //clw note����ɫȫ0����ɫȫ0xFF

	// Initialize image loading for PNGs
	//clw note:�����ǣ����û��libpng16-16.dll���dll������ͻ�ʧ�ܣ�Ȼ��ͻ����ȱ��dll����ʾ�����û��������ǲ��ܼ���.png�ļ��ģ����������Ҫ�ȳ�ʼ��һ�£�ȷ����libpng16-16.dll
	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) 
	{
		Log("Unable to init SDL_image: %s", IMG_GetError());
		return false;
	}

	//Load all of our Textures (see TextureBank class for expected folder)
	//clw note��TextureBank::Init()��ʼ����ʱ�����ĳ���ļ���������ͼƬ������ڲ�ʵ��
	if(TextureBank::Init() == false)   //clw note:ֻ��CApp::GetInstance()->GetRenderer()ʧ�ܲŻ᷵��false������������
	{
		Log("Unable to init TextureBank");
		return false;
	}
	if (Entity1.OnLoad("./entity1.bmp", 64, 64, 8) == false)
		return false;
	if (Entity2.OnLoad("./entity2.bmp", 64, 64, 8) == false)
		return false;
	Entity2.X = 100;

	CEntity::EntityList.push_back(&Entity1);
	CEntity::EntityList.push_back(&Entity2);

	if (CArea::AreaControl.OnLoad("./maps/1.area") == false) 
	{
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------
void CApp::Loop() 
{
	for (int i = 0; i < CEntity::EntityList.size(); i++) 
	{
		if (!CEntity::EntityList[i]) 
			continue;
		CEntity::EntityList[i]->OnLoop();
	}
}

//------------------------------------------------------------------------------
void CApp::Render() 
{
	SDL_RenderClear(Renderer);

	//Texture* pMyTexture = TextureBank::Get("1"); 
	// You should really check your pointers 
	// ��ע��Get�Ĳ���IDһ��Ҫ��TexList���вſ���


	//if(pMyTexture != NULL)
		//pMyTexture->Render((GetWindowWidth() - pMyTexture->GetWidth()) / 2, (GetWindowHeight() - pMyTexture->GetHeight()) / 2); 


	//Texture* pMyTexture = TextureBank::Get("yoshi2");
	//if (pMyTexture != NULL)
		//pMyTexture->Render((GetWindowWidth() - pMyTexture->GetWidth()) / 2, \
		                   (GetWindowHeight() - pMyTexture->GetWidth()) / 2, \
			                pMyTexture->GetWidth(), \
			pMyTexture->GetWidth(), \
			                0, \
			                Anim_Yoshi.GetCurrentFrame() * pMyTexture->GetWidth(), \
			                pMyTexture->GetWidth(), \
			                pMyTexture->GetWidth());


	for (int i = 0; i < CEntity::EntityList.size(); i++) 
	{
		if (!CEntity::EntityList[i]) 
			continue;
		CEntity::EntityList[i]->OnRender();
	}

	CArea::AreaControl.OnRender(CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());

	SDL_RenderPresent(Renderer);
}

//------------------------------------------------------------------------------
void CApp::Cleanup() 
{
	for (int i = 0; i < CEntity::EntityList.size(); i++) 
	{
		if (!CEntity::EntityList[i]) 
			continue;
		CEntity::EntityList[i]->OnCleanup();
	}
	CEntity::EntityList.clear();

	CArea::AreaControl.OnCleanup();

	TextureBank::Cleanup();

	if(Renderer) 
	{
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
	}

	if(Window) 
	{
		SDL_DestroyWindow(Window);
		Window = NULL;
	}

	IMG_Quit();
	SDL_Quit();
}

//------------------------------------------------------------------------------
int CApp::Execute(int argc, char* argv[]) 
{
	if(!Init()) 
		return 0;

	SDL_Event Event;
	
	while(Running) 
	{
		while(SDL_PollEvent(&Event) != 0) 
		{
			OnEvent(&Event);

			if(Event.type == SDL_QUIT) 
				Running = false;

			//User presses a key
			else if (Event.type == SDL_KEYDOWN  /* && Event.key.repeat == 0*/)
			{
				//Select surfaces based on key press
				switch (Event.key.keysym.sym)
				{
				case SDLK_UP:
					CCamera::CameraControl.OnMove(0, 15);   //clw note:ԭΪOnMove(0, 5)
					break;

				case SDLK_DOWN:
					CCamera::CameraControl.OnMove(0, -15);
					break;

				case SDLK_LEFT:
					CCamera::CameraControl.OnMove(15, 0);
					break;

				case SDLK_RIGHT:
					CCamera::CameraControl.OnMove(-15, 0); 
					break;

				default:
					break;
				}
			}
		}

		Loop();
		Render();

		//SDL_Delay(0.1); // Breath
	}

	Cleanup();

	return 1;
}

//==============================================================================
SDL_Renderer* CApp::GetRenderer() 
{ 
	return Renderer; 
}

//==============================================================================

int CApp::GetWindowWidth()  { return WWIDTH; }
int CApp::GetWindowHeight() { return WWIDTH; }

//==============================================================================
