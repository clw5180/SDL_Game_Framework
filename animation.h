#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL.h>

class CAnimation 
{
public:
	CAnimation();

	void OnAnimate();

	void SetFrameRate(int Rate) { FrameRate = Rate; }

	void SetCurrentFrame(int Frame) { if (Frame < 0 || Frame >= MaxFrames) return;  CurrentFrame = Frame;}

	int GetCurrentFrame() { return CurrentFrame; }

	void SetMaxFrames(int Frame) { if (Frame < 0 ) return; MaxFrames = Frame; }

private:
	int    CurrentFrame;

	int     FrameInc;

	int     FrameRate; //Milliseconds

	long    OldTime;

	int    MaxFrames;


	/*The next interesting tid bit is Oscillate and FrameInc.
	  Not that I wanted to confuse anyone by adding this, but I feel it's necessary for
	  certain things later on. Basically, when the Oscillate flag is true, the animation
	  will increase frames, and then decrease frames. If we had an animation with 10 frames,
	  it would do something like this:

		  0 1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1 2 ...

	  You see, it goes up to 9, and then decreases back down to 0, and so on.
	  There are some interesting uses for this, but we'll get into that in other lessons.
	  So how does this work? Take a look at the OnAnimate function. */
	bool    Oscillate;

};

#endif