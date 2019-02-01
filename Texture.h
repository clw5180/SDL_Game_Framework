//==============================================================================
/*
	Texture class for wrapping SDL Textures

	3/13/2014
    SDLTutorials.com
    Tim Jones
*/
//==============================================================================
#ifndef __TEXTURE_H__
	#define __TEXTURE_H__

#include <SDL.h>
#include <SDL_image.h>

#include <string>

class Texture {
	private:
		std::string Filename;

		int Width = 0;
		int Height = 0;

		SDL_Renderer* Renderer = NULL;
		SDL_Texture* SDLTexture = NULL;

	public:
		Texture();
		~Texture();

		bool Load(SDL_Renderer* Renderer, std::string Filename);

		void Render(int X, int Y, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void Render(int X, int Y, int Width, int Height, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void RenderEx(int X, int Y, int SX, int SY, int SWidth, int SHeight, double _angle = 0, const SDL_Point* _alpha = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

		int GetWidth();
		int GetHeight();
};

#endif
