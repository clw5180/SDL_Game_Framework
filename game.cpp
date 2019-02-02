//==============================================================================
#include "game.h"
#include "log.h"
#include <vector>
#include "filemanager.h"
#include "define.h"
#include "area.h"
#include "camera.h"
#include "inputhandler.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

//==============================================================================
CGame* CGame::s_pInstance = NULL;

//------------------------------------------------------------------------------
int CGame::Execute(int argc, char* argv[])
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
void CGame::HandleEvents() 
{
	TheInputHandler::Instance()->update();
}

//------------------------------------------------------------------------------
bool CGame::Init() 
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

	//Load all of our Textures (see CTextureBank class for expected folder)
	//clw note��CTextureBank::Init()��ʼ����ʱ�����ĳ���ļ���������ͼƬ������ڲ�ʵ��
	//ֻ��CGame::GetInstance()->GetRenderer()ʧ�ܲŻ᷵��false������������
	//���ʧ�ܻᱨ���������£�
	//FindFirstFile failed (3)
	//Unable to open directory : E:\Projects\SDL_engine_test / data
	if(CTextureBank::Init() == false)   
	{
		Log("Unable to init CTextureBank");
		return false;
	}

	/*********************************************************/
	/* clw modify 20190201:������sprite */
	if (Entity1.OnLoad("./entity1.bmp", 64, 64, 8) == false)
		return false;
	if (Entity2.OnLoad("./entity2.bmp", 64, 64, 8) == false)
		return false;
	if (myTexture.Load(CGame::GetInstance()->GetRenderer(), "./3.png") == false)
		return false;
	
	Entity1.SetX(WWIDTH / 2 - 40);
	Entity1.SetY((WHEIGHT - 64) / 2);
	Entity2.SetX(WWIDTH / 2 + 40);
	Entity2.SetY((WHEIGHT - 64) / 2);

	//clw note��ע��GetEntityList��ط����������ͣ�����������GetEntityList������������
	CEntity::GetEntityList().push_back(&Entity1);
	CEntity::GetEntityList().push_back(&Entity2);
	/*********************************************************/

	if (CArea::GetAreaControl().OnLoad("./maps/1.area") == false) 
	{
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------
void CGame::Render() 
{
	SDL_RenderClear(Renderer);

	//CTexture* pMyTexture = CTextureBank::Get("1");  
	// ��ע��Get�Ĳ���IDһ��Ҫ��TexList���вſ��ԣ�should really check your pointers

	//clw note���۲�һ��������ƶ�
	//static int tempX = 0;
	//static int tempY = 0;
	//CCamera::CameraControl.SetTarget(&tempX, &tempY);
	//tempX++;
	//tempY++;

	CArea::GetAreaControl().OnRender(CCamera::GetCameraControl().GetX(), CCamera::GetCameraControl().GetY());
	

	//myTexture.Render(CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());

	for (int i = 0; i < CEntity::GetEntityList().size(); i++)
	{
		if (!CEntity::GetEntityList()[i])
			continue;
		CEntity::GetEntityList()[i]->OnRender();
	}

	SDL_RenderPresent(Renderer);
}

// Update made by clw
void CGame::Update()
{
	for (int i = 0; i < CEntity::GetEntityList().size(); i++)
	{
		if (!CEntity::GetEntityList()[i])
			continue;
		CEntity::GetEntityList()[i]->Update();
	}

	CCamera::GetCameraControl().Update();
}

//------------------------------------------------------------------------------
void CGame::Cleanup() 
{

	for (int i = 0; i < CEntity::GetEntityList().size(); i++) 
	{
		if (!CEntity::GetEntityList()[i])
			continue;
		CEntity::GetEntityList()[i]->OnCleanup();
	}
	CEntity::GetEntityList().clear();


	CArea::GetAreaControl().OnCleanup();

	CTextureBank::Cleanup();

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
SDL_Renderer* CGame::GetRenderer() 
{ 
	return Renderer; 
}

//==============================================================================

int CGame::GetWindowWidth()  { return WWIDTH; }
int CGame::GetWindowHeight() { return WWIDTH; }

//==============================================================================
