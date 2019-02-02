//==============================================================================
#include "texture.h"
#include "log.h"

//==============================================================================
CTexture::CTexture() {
}

//------------------------------------------------------------------------------
CTexture::~CTexture() 
{
	if(SDLTexture) 
	{
		SDL_DestroyTexture(SDLTexture);
		SDLTexture = NULL;
	}
}

//==============================================================================
bool CTexture::Load(SDL_Renderer* Renderer, std::string Filename) 
{
	if(Renderer == NULL) 
	{
		Log("Bad SDL renderer passed");
		return false;
	}

	this->Renderer = Renderer;
	this->Filename = Filename;

	//clw note��������TempSurface��ԱȽ��鷳����һ�������ŵ��ǿ���ʹ��SDL_SetColorKey����ɫ��ʾͼƬ
	//          �������Ҫ��ɫ�Ļ���ֱ����IMG_LoadTexture����������򵥵����˾��ȡ�����
	//          ֻ��Ҫȥ��SDL_Surface�Ĺ�����ֱ�Ӽ���texture*/
	//          ���磺SDLTexture = IMG_LoadTexture(Renderer, Filename.c_str());
	SDL_Surface* TempSurface = IMG_Load(Filename.c_str());//����Ҫ��libpng16-16.dll���dll���������.png��ʧ�ܣ�
	//�����.jpg��Ҫlibjpeg-9.dll
	
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
		Log("Unable to create SDL CTexture : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}
	
    // Grab dimensions
	SDL_QueryTexture(SDLTexture, NULL, NULL, &Width, &Height);

	//Log("CTexture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);

	SDL_FreeSurface(TempSurface);
	return true;
}

//------------------------------------------------------------------------------
void CTexture::Render(int X, int Y, SDL_RendererFlip flip)
{
	Render(X, Y, Width, Height, flip);
}

//------------------------------------------------------------------------------
void CTexture::Render(int X, int Y, int Width, int Height, SDL_RendererFlip flip)
{
	SDL_Rect Destination = {X, Y, Width, Height};

	SDL_RenderCopyEx(Renderer, SDLTexture, NULL, &Destination, 0, 0, flip);
}

//------------------------------------------------------------------------------
void CTexture::Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight, SDL_RendererFlip flip)
{
	SDL_Rect Source = {SX, SY, SWidth, SHeight};
	SDL_Rect Destination = {X, Y, Width, Height};

	SDL_RenderCopyEx(Renderer, SDLTexture, &Source, &Destination, 0, 0, flip);
}

void CTexture::RenderEx(int X, int Y, int SX, int SY, int SWidth, int SHeight, double _angle, const SDL_Point* _alpha, SDL_RendererFlip flip )
{
	SDL_Rect Source = { SX, SY, SWidth, SHeight };
	SDL_Rect Destination;
	Destination.x = X;
	Destination.y = Y;
	Destination.w = SWidth;  //clw note��ע�⣺����ط�����ø�ֵ���������Ĭ��ֵ0�������Ļ�Ͼ�ʲôҲû�У�����
	Destination.h = SHeight;

	SDL_RenderCopyEx(Renderer, SDLTexture, &Source, &Destination, _angle, 0, flip);
}


//------------------------------------------------------------------------------
int CTexture::GetWidth()  { return Width;  }
int CTexture::GetHeight() { return Height; }

//==============================================================================