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
	
	//clw note:����������Ͳ������ã��ڵ��ú����ĵط��Ὣ��������ֵ���Ƹ���ʱ���󣻵�����������������ʱ��û�и��Ʒ���ֵ���෴�����ص��Ƕ�����
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

	Vector2D m_velocity; //clw note��������Ҫ�����жϷ���һ����Camera���ٶ�������

	// rotation
	double m_angle;

	static std::vector<CEntity*> EntityList;
};

#endif 