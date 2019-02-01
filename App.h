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

	bool Running() { return m_bRunning; }

	void Quit() { m_bRunning = false; }

private:
	static CApp* s_pInstance;
	CApp() {}

	bool m_bRunning = true;

	SDL_Window* Window = NULL;
	SDL_Renderer* Renderer = NULL;
	SDL_Surface* PrimarySurface = NULL;

	//static const int WindowWidth = 512;  //clw note：写成静态常量成员，不如在一个.h头文件中define
	//static const int WindowHeight = 384;

	Texture* TestTexture;

	CEntity Entity1;
	CEntity Entity2;
	Texture myTexture;

	// Capture SDL Events
	void HandleEvents();

	// Initialize our SDL game / app
	bool Init();

	// Update made by clw
	void Update();

	// Render loop (draw)
	void Render();


	// Free up resources
	void Cleanup();


};


#endif
