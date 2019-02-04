#ifndef __SDLGAMEOBJECT_H__
#define __SDLGAMEOBJECT_H__

#include <SDL.h>
#include "gameobject.h"

using namespace std;

class CSDLGameObject : public CGameObject
{
public:
	
	virtual ~CSDLGameObject() {}

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(std::unique_ptr<CLoaderParams> const &pParams);

	virtual std::string type() { return "CSDLGameObject"; }

protected:
	CSDLGameObject();

	void doDyingAnimation()
	{
		m_currentFrame = int(((SDL_GetTicks() / (1000 / 10)) % m_numFrames));

		if (m_dyingCounter == m_dyingTime)
		{
			m_bDead = true;
		}
		m_dyingCounter++;
	}

	int m_moveSpeed;

	// how long the death animation takes, along with a counter
	int m_dyingTime;
	int m_dyingCounter;

	// has the explosion sound played?
	bool m_bPlayedDeathSound;

};

#endif