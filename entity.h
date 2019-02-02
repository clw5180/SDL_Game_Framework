#ifndef  __ENTITY_H__
#define  __ENTITY_H__

#include <vector>
#include "animation.h"
#include "texture.h"
#include "vector2D.h"

class CEntity 
{
public:
	CEntity();

	virtual ~CEntity() {}

	virtual bool OnLoad(std::string File, int Width, int Height, int MaxFrames);

	virtual void Update();

	virtual void OnRender(SDL_RendererFlip flip = SDL_FLIP_NONE);

	virtual void OnCleanup();

	void SetX(int X) { this->X = X; }
	void SetY(int Y) { this->Y = Y; }
	
	//clw note:如果返回类型不是引用，在调用函数的地方会将函数返回值复制给临时对象；当函数返回引用类型时，没有复制返回值，相反，返回的是对象本身。
	static std::vector<CEntity*>& GetEntityList() { return EntityList; }

protected:
	CAnimation  Anim_Control;

	CTexture*    Tex_Entity;

private:
	
	int           X;
	int           Y;
	int             Width;
	int             Height;

	int             AnimState;

	SDL_RendererFlip     m_flip;

	Vector2D m_velocity; //clw note：这里主要用来判断方向，一般是Camera的速度起作用

	// rotation
	double m_angle;

	static std::vector<CEntity*> EntityList;
};

#endif 