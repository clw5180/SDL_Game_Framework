#pragma once

#include <vector>

#include "animation.h"
#include "Texture.h"

class CEntity 
{
public:
	static std::vector<CEntity*>    EntityList;

protected:
	CAnimation  Anim_Control;

	Texture*    Tex_Entity;

public:
	float           X;
	float           Y;

	int             Width;
	int             Height;

	int             AnimState;

public:
	CEntity();

	virtual ~CEntity() {}

public:
	virtual bool OnLoad(std::string File, int Width, int Height, int MaxFrames);

	virtual void OnLoop();

	virtual void OnRender();

	virtual void OnCleanup();
};