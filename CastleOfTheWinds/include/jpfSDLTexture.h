#ifndef JPFSDLTEXTURE_H
#define JPFSDLTEXTURE_H

//SDL Include
#include <SDL2/SDL.h>
//User Include
#include "logSDLError.h"

/**
* Loads a BMP image into a texture on the rendering device.
* @param file The BMP file to be loaded.
* @param renderer The renderer to load texture onto.
* @return the loaded texture or a nullptr in case of error.
**/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* renderer) {
	SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
	//Test Texture Load
	if (texture == nullptr) {
		logSDLError(std::cout, "loadTexture");
	}
	return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rectangle
* taking a clip of the texture if desired (as opposed to all of it)
* @param texture The source texture to be drawn.
* @param renderer The rednerer we are drawing to.
* @param dest The destination rectangle to render the texture to.
* @param clip The subsection of the texture to draw (clipping rectangle)
*				default of nullptr draws the entire texture. 
**/
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect dest, SDL_Rect* clip = nullptr) {
	SDL_RenderCopy(renderer, texture, clip, &dest);
}

/**
* Draw an SDL_Texture to a given SDL_Renderer at position x, y.
* Scales texture width and height.
* @param texture The source texture to be drawn.
* @param renderer The renderer we are drawing to.
* @param x The x coordinate to draw to.
* @param y The y coordinate to draw to.
* @param w The width to draw the texture to.
* @param h The height to draw the texture to.
**/
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h) {
	//Setup the destination rectangle we are drawing to.
	SDL_Rect dest;
	dest.x = x; dest.y = y;
	dest.w = w; dest.h = h;
	//Query the texture to get its width and height.
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

/**
* Draw an SDL_Texture to a given SDL_Renderer at position x, y.
* Preserves texture width and height with no scaling.
* @param texture The source texture to be drawn.
* @param renderer The render we are drawing to.
* @param x The x coordinate to draw to.
* @param y The y coordinate to draw to. 
**/
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	if (clip != nullptr) {
		dest.w = clip->w;
		dest.h = clip->h;
	} else {
		SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	}
	renderTexture(texture, renderer, dest, clip);
}

#endif
