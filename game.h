#ifndef __CLW_GAME_H__
#define __CLW_GAME_H__

#include <SDL.h>

#include "texturemanager.h"

#include "entity.h"

#include "gamestatemachine.h"

#include "define.h"

class CGame
{
public:
	int Execute(int argc, char* argv[]);

	// Capture SDL Events
	void HandleEvents();

	// Initialize our SDL game
	bool Init();

	// Update made by clw
	void Update();

	// Render loop (draw)
	void Render();

	// Free up resources
	void Cleanup();

	SDL_Renderer* GetRenderer() const { return m_pRenderer; }
	CGameStateMachine* GetStateMachine() { return m_pGameStateMachine; }

	static CGame* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new CGame();
		}
		return s_pInstance;
	}

	bool running() { return m_bRunning; }

	void quit() { m_bRunning = false; }

	//==============================================================================

	int GetWindowWidth() { return WWIDTH; }
	int GetWindowHeight() { return WWIDTH; }

	//==============================================================================

	bool Running() { return m_bRunning; }

	void Quit() { m_bRunning = false; }

private:
	static CGame* s_pInstance;
	CGame() {}

	bool m_bRunning = true;

	SDL_Window* Window = NULL;
	SDL_Renderer* m_pRenderer = NULL;
	SDL_Surface* PrimarySurface = NULL; //clw note：作用？？

	CGameStateMachine* m_pGameStateMachine;

	//static const int WindowWidth = 512;  //clw note：写成静态常量成员，不如在一个.h头文件中define
	//static const int WindowHeight = 384;

	CTexture* TestTexture;

	CEntity Entity1;
	CEntity Entity2;
	CTexture myTexture;
};

#endif
