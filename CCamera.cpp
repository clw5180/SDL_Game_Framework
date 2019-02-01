#include "CCamera.h"
#include "InputHandler.h"

CCamera CCamera::CameraControl;

CCamera::CCamera() 
{
	X = Y = 0;

	m_velocity.setX(0);
	m_velocity.setY(0);

	TargetX = TargetY = NULL;

	TargetMode = TARGET_MODE_NORMAL;
}

//void CCamera::OnMove(int MoveX, int MoveY) 
//{
//	X += MoveX;
//	Y += MoveY;
//}
// clw modify 
void CCamera::SetVelocity(int velocity_X, int velocity_Y)
{
	m_velocity.setX(velocity_X);
	m_velocity.setY(velocity_Y);
}
void CCamera::HandleInput()
{
	//handle keys
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) /*&& m_position.getY() > 0*/)
	{
		m_velocity.setY(5);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) /*&& (m_position.getY() + m_height) < TheGame::Instance()->getGameHeight() - 10*/)
	{
		m_velocity.setY(-5);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) /*&& m_position.getX() > 0*/)
	{
		m_velocity.setX(5);
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) /*&& (m_position.getX() + m_width) < TheGame::Instance()->getGameWidth()*/)
	{
		m_velocity.setX(-5);
	}
}
void CCamera::Update()
{
	// reset velocity
	// clw note：这里非常重要，确保没有按键按下时，Camera是静止的。
	m_velocity.setX(0);
	m_velocity.setY(0);

	HandleInput();

	X += m_velocity.getX();
	Y += m_velocity.getY();
}


int CCamera::GetX() 
{
	if (TargetX != NULL) 
	{
		if (TargetMode == TARGET_MODE_CENTER) 
		{
			return *TargetX - (WWIDTH / 2);
		}

		return *TargetX;
	}

	return X;
}

int CCamera::GetY() 
{
	if (TargetY != NULL) 
	{
		if (TargetMode == TARGET_MODE_CENTER) 
		{
			return *TargetY - (WHEIGHT / 2);
		}

		return *TargetY;
	}

	return Y;
}

void CCamera::SetPos(int X, int Y) 
{
	this->X = X;
	this->Y = Y;
}

void CCamera::SetTarget(int* X, int* Y) 
{
	TargetX = X;
	TargetY = Y;
}