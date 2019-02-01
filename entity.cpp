#include "entity.h"
#include "App.h"
#include "Log.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity() 
{
	Tex_Entity = new Texture();

	X = Y = 0.0f;

	Width = Height = 0;

	AnimState = 0;
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

void CEntity::OnLoop() 
{
	Anim_Control.OnAnimate();
}

void CEntity::OnRender() 
{
	if (Tex_Entity == NULL) 
		return;
	Tex_Entity->Render(X, Y, AnimState * Width, Anim_Control.GetCurrentFrame() * Height, Width, Height);
}

void CEntity::OnCleanup() 
{
	//if (Surf_Entity) 
	//{
	//	SDL_FreeSurface(Surf_Entity);
	//}

	//Surf_Entity = NULL;
}
