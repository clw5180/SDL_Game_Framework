#pragma once

#include <vector>

#include "animation.h"
#include "Texture.h"

#include "Vector2D.h"

class CEntity 
{
public:
	static std::vector<CEntity*>    EntityList;

protected:
	CAnimation  Anim_Control;

	Texture*    Tex_Entity;

public:
	int           X;
	int           Y;

	int             Width;
	int             Height;

	int             AnimState;

	SDL_RendererFlip     m_flip;

	Vector2D m_velocity; //clw note：这里主要用来判断方向，一般是Camera的速度起作用

	// rotation
	double m_angle;

public:
	CEntity();

	virtual ~CEntity() {}

	virtual bool OnLoad(std::string File, int Width, int Height, int MaxFrames);

	virtual void Update();

	virtual void OnRender(SDL_RendererFlip flip = SDL_FLIP_NONE);

	virtual void OnCleanup();
};