#include "animation.h"

CAnimation::CAnimation() 
{
	CurrentFrame = 0;
	MaxFrames = 0;
	FrameInc = 1;
	FrameRate = 1000 / 16; //clw note：这里的帧速率是以时间来衡量的，单位miliseconds
	                       //          是1帧所用的时间；因此值越大，速度越慢
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
			if (CurrentFrame >= MaxFrames - 1) //clw note：这里应该是-1，因为0 1 2 3 4 5 6再到7的时候
				                               //就应该准备开始减了，否则就会把不存在的MaxFrames显示
				                               //出来；而上面是CurrentFrame >= MaxFrames
				                               //因为0 1 2 3 4 5 6 7虽然到了8但是立刻就被清0了；
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

