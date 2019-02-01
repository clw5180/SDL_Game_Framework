//==============================================================================
/*
	Primary application class

	3/11/2014
	SDLTutorials.com
	Tim Jones
*/
//==============================================================================
#ifndef __APP_H__
#define __APP_H__

#include <SDL.h>

#include "TextureBank.h"

#include "entity.h"

class CApp
{
public:
	int Execute(int argc, char* argv[]);

	SDL_Renderer* GetRenderer();

	static CApp* GetInstance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new CApp();
		}
		return s_pInstance;
	}

	static int GetWindowWidth();
	static int GetWindowHeight();

private:
	static CApp* s_pInstance;
	CApp() {}

	bool Running = true;

	SDL_Window* Window = NULL;
	SDL_Renderer* Renderer = NULL;
	SDL_Surface* PrimarySurface = NULL;

	//static const int WindowWidth = 512;  //clw note：这里作者把窗口大小写成静态常量成员
	//static const int WindowHeight = 384;

	Texture* TestTexture;

	CEntity Entity1;
	CEntity Entity2;

	// Capture SDL Events
	void OnEvent(SDL_Event* Event);

	// Initialize our SDL game / app
	bool Init();

	// Logic loop
	void Loop();

	// Render loop (draw)
	void Render();

	// Free up resources
	void Cleanup();
};


#endif
