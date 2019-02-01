//==============================================================================
#include "Texture.h"
#include "Log.h"

//==============================================================================
Texture::Texture() {
}

//------------------------------------------------------------------------------
Texture::~Texture() 
{
	if(SDLTexture) 
	{
		SDL_DestroyTexture(SDLTexture);
		SDLTexture = NULL;
	}
}

//==============================================================================
bool Texture::Load(SDL_Renderer* Renderer, std::string Filename) 
{
	if(Renderer == NULL) 
	{
		Log("Bad SDL renderer passed");
		return false;
	}

	this->Renderer = Renderer;
	this->Filename = Filename;

	//clw note：这里用TempSurface相对比较麻烦，但一个最大的优点是可以使用SDL_SetColorKey来扣色显示图片
	//          如果不需要扣色的话，直接用IMG_LoadTexture，这个函数简单得让人惊讶。我们
	//          只需要去掉SDL_Surface的工作，直接加载texture*/
	//          例如：SDLTexture = IMG_LoadTexture(Renderer, Filename.c_str());
	SDL_Surface* TempSurface = IMG_Load(Filename.c_str());//必须要有libpng16-16.dll这个dll，否则加载.png会失败！
	//如果是.jpg需要libjpeg-9.dll
	
	if (TempSurface == NULL)
	{
		Log("Unable to load image : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}

	//Color key image
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0xFF, 0, 0xFF));

	// Convert SDL surface to a texture
	if ((SDLTexture = SDL_CreateTextureFromSurface(Renderer, TempSurface)) == NULL)
	{
		Log("Unable to create SDL Texture : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}
	
    // Grab dimensions
	SDL_QueryTexture(SDLTexture, NULL, NULL, &Width, &Height);

	//Log("Texture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);

	SDL_FreeSurface(TempSurface);
	return true;
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y) 
{
	Render(X, Y, Width, Height);
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height) 
{
	SDL_Rect Destination = {X, Y, Width, Height};

	SDL_RenderCopy(Renderer, SDLTexture, NULL, &Destination);
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight) 
{
	SDL_Rect Source = {SX, SY, SWidth, SHeight};
	SDL_Rect Destination = {X, Y, Width, Height};

	SDL_RenderCopy(Renderer, SDLTexture, &Source, &Destination);
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int SX, int SY, int SWidth, int SHeight)
{
	SDL_Rect Source = { SX, SY, SWidth, SHeight };
	SDL_Rect Destination;
	Destination.x = X;
	Destination.y = Y;
	Destination.w = SWidth;  //clw note：这个地方必须得给值，否则就是默认值0，因此屏幕上就什么也没有！！！
	Destination.h = SHeight;

	SDL_RenderCopy(Renderer, SDLTexture, &Source, &Destination);
}


//------------------------------------------------------------------------------
int Texture::GetWidth()  { return Width;  }
int Texture::GetHeight() { return Height; }

//==============================================================================