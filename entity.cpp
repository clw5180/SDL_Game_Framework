#include "entity.h"
#include "game.h"
#include "log.h"
#include "inputhandler.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity() 
{
	Tex_Entity = new CTexture();

	X = Y = 0;

	Width = Height = 0;

	AnimState = 0;

	m_flip = SDL_FLIP_NONE;

	m_velocity.setX(0);
	m_velocity.setY(0);
}

bool CEntity::OnLoad(std::string File, int Width, int Height, int MaxFrames)
{
	if (Tex_Entity == NULL)
		return false;

	if (Tex_Entity->Load(CGame::GetInstance()->GetRenderer(), File) == false)
	{
		Log("Unable to Load CTexture!");
		return false;
	}

	this->Width = Width;
	this->Height = Height;

	Anim_Control.SetMaxFrames(MaxFrames);

	return true;
}

void CEntity::Update() 
{
	Anim_Control.OnAnimate();

	//clw modify
	//reset velocity，很重要
	m_velocity.setX(0);

	if (CInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(1);
		m_flip = SDL_FLIP_NONE;
	}
	else if (CInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-1);
		m_flip = SDL_FLIP_HORIZONTAL;
	}

	// update the animation
	if (m_velocity.getX() < 0)
	{
		m_angle = -10.0;
	}
	else if (m_velocity.getX() > 0)
	{
		m_angle = 10.0;
	}
	else
	{
		Anim_Control.SetCurrentFrame(0); //clw note：如果没有键按下，则保持entity静止
		m_angle = 0.0;
	}
}

void CEntity::OnRender(SDL_RendererFlip flip)
{
	if (Tex_Entity == NULL) 
		return;

	Tex_Entity->RenderEx(X, Y, AnimState * Width, Anim_Control.GetCurrentFrame() * Height, Width, Height, m_angle, 0, m_flip);
}

void CEntity::OnCleanup() 
{
	//if (Surf_Entity) 
	//{
	//	SDL_FreeSurface(Surf_Entity);
	//}

	//Surf_Entity = NULL;
}
