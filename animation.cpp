#include "animation.h"

CAnimation::CAnimation() 
{
	CurrentFrame = 0;
	MaxFrames = 0;
	FrameInc = 1;
	FrameRate = 1000 / 16; //clw note�������֡��������ʱ���������ģ���λmiliseconds
	                       //          ��1֡���õ�ʱ�䣻���ֵԽ���ٶ�Խ��
	OldTime = 0;

	Oscillate = false;
}

void CAnimation::OnAnimate() 
{
	/************************************************************************
	Bug Fix: if(CurrentFrame >= MaxFrames - 1) needs to be if(CurrentFrame >= 
	MaxFrames). Kudos to everyone in the comments mentioning this.

    Bug Fix: There was an error with placing CurrentFrame += FrameInc; 
	after the if statement, it should have been placed before the if statement. 
	What would happen is if the animation had MaxFrames = 0, 
	it would still increase the CurrentFrame to 1. 
	Thanks Alexander Mangel for helping find this bug!
	************************************************************************/
	if (OldTime + FrameRate > SDL_GetTicks())
	{
		return;
	}

	OldTime = SDL_GetTicks();

	CurrentFrame += FrameInc;

	if (!Oscillate) 
	{
		if (CurrentFrame >= MaxFrames)
		{
			CurrentFrame = 0;
		}
	}
	else 
	{
		if (FrameInc > 0)
		{
			if (CurrentFrame >= MaxFrames - 1) //clw note������Ӧ����-1����Ϊ0 1 2 3 4 5 6�ٵ�7��ʱ��
				                               //��Ӧ��׼����ʼ���ˣ�����ͻ�Ѳ����ڵ�MaxFrames��ʾ
				                               //��������������CurrentFrame >= MaxFrames
				                               //��Ϊ0 1 2 3 4 5 6 7��Ȼ����8�������̾ͱ���0�ˣ�
			{
				FrameInc = -FrameInc;
			}
		}
		else
		{
			if (CurrentFrame <= 0)
			{
				FrameInc = -FrameInc;
			}
		}
	}
}

