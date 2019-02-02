#ifndef __AMERA_H__
#define __AMERA_H__

#include <SDL.h>
#include "define.h"
#include "vector2D.h"

enum 
{
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class CCamera 
{
public:
	CCamera();

	static CCamera& GetCameraControl() { return CameraControl; }

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

	int TargetMode;

	static CCamera CameraControl;
};

#endif