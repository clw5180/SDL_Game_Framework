//==============================================================================
#include "App.h"
#include "Log.h"

#include <vector>
#include "FileManager.h"

#include "Define.h"

#include "CArea.h"
#include "CCamera.h"

#include "InputHandler.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

//==============================================================================
CApp* CApp::s_pInstance = NULL;

//------------------------------------------------------------------------------
int CApp::Execute(int argc, char* argv[])
{
	Uint32 frameStart, frameTime;

	if (!Init())
	{
		Log("clw��Unable to Init SDL: %s", SDL_GetError());
		return -1;
	}
		
	while (Running())
	{
		frameStart = SDL_GetTicks();

		HandleEvents();
		Update();
		Render();	

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}

	Log("clw��game closing...\n");
	Cleanup();
	return 0;
}


//------------------------------------------------------------------------------
void CApp::HandleEvents() 
{
	TheInputHandler::Instance()->update();
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

	/*********************************************************/
	/* clw modify 20190201:������sprite */
	if (Entity1.OnLoad("./entity1.bmp", 64, 64, 8) == false)
		return false;
	if (Entity2.OnLoad("./entity2.bmp", 64, 64, 8) == false)
		return false;
	if (myTexture.Load(CApp::GetInstance()->GetRenderer(), "./3.png") == false)
		return false;
	
	Entity1.X = WWIDTH / 2 - 40;
	Entity1.Y = (WHEIGHT - 64) / 2;
	Entity2.X = WWIDTH / 2 + 40;
	Entity2.Y = (WHEIGHT - 64) / 2;

	CEntity::EntityList.push_back(&Entity1);
	CEntity::EntityList.push_back(&Entity2);
	/*********************************************************/

	if (CArea::AreaControl.OnLoad("./maps/1.area") == false) 
	{
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------
void CApp::Render() 
{
	SDL_RenderClear(Renderer);

	//Texture* pMyTexture = TextureBank::Get("1");  
	// ��ע��Get�Ĳ���IDһ��Ҫ��TexList���вſ��ԣ�should really check your pointers



	//CArea::AreaControl.OnRender(CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());

	myTexture.Render(CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());

	for (int i = 0; i < CEntity::EntityList.size(); i++)
	{
		if (!CEntity::EntityList[i])
			continue;
		CEntity::EntityList[i]->OnRender();
	}

	SDL_RenderPresent(Renderer);
}

// Update made by clw
void CApp::Update()
{
	for (int i = 0; i < CEntity::EntityList.size(); i++)
	{
		if (!CEntity::EntityList[i])
			continue;
		CEntity::EntityList[i]->Update();
	}

	CCamera::CameraControl.Update();
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


//==============================================================================
SDL_Renderer* CApp::GetRenderer() 
{ 
	return Renderer; 
}

//==============================================================================

int CApp::GetWindowWidth()  { return WWIDTH; }
int CApp::GetWindowHeight() { return WWIDTH; }

//==============================================================================
