#include "entity.h"
#include "App.h"
#include "Log.h"
#include "InputHandler.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity() 
{
	Tex_Entity = new Texture();

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

	if (Tex_Entity->Load(CApp::GetInstance()->GetRenderer(), File) == false)
	{
		Log("Unable to Load Texture!");
		return false;
	}

	this->Width = Width;
	this->Height = Height;

	Anim_Control.MaxFrames = MaxFrames;

	return true;
}

void CEntity::Update() 
{
	Anim_Control.OnAnimate();

	//clw modify
	//reset velocity������Ҫ
	m_velocity.setX(0);

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(1);
		m_flip = SDL_FLIP_NONE;
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
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
		Anim_Control.SetCurrentFrame(0); //clw note�����û�м����£��򱣳�entity��ֹ
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
