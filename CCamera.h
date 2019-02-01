#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include <SDL.h>

#include "Define.h"
#include "Vector2D.h"

enum {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class CCamera 
{
public:
	static CCamera CameraControl;

	int TargetMode;

	CCamera();

	//void OnMove(int MoveX, int MoveY);
	void SetVelocity(int velocityX, int velocityY);

	int GetX();
	int GetY();

	void SetPos(int X, int Y);

	void SetTarget(int* X, int* Y);

	void HandleInput();
	void Update();

private:
	int X;
	int Y;

	Vector2D m_velocity;

	int* TargetX;
	int* TargetY;
};

#endif