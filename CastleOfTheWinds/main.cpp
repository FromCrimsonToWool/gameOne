/**
PROJECT GAMMA: Castle of the Winds Redux (Julien)
@author Julien Fernandes
@version 0.01a
**/

//Standard Include
#include <iostream>
#include <fstream>
#include <string>
//SDL Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//User Include
#include "include/res_path.h"
#include "include/cleanup.h"
#include "include/logSDLError.h"
#include "include/jpfSDLTexture.h"
#include "include/core.h"
#include "include/shell.h"

//DEBUG Variable
int debug;

//Settings Input Variables
std::ifstream fileRead; //Used to read from an initial settings file.

//Initial Settings Variables
int screenX, screenY; //Used to temporarily store read values from the settings file.

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
const int TILE_SIZE = 40;

int main(int argc, char** argv) {
	//PRE GAME LOOP
	//Initialize SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logSDLError(std::cout, "SDL_INIT");
		return 1;
	}

	//Initialize SDL image subsystem
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_INIT");
		SDL_Quit();
		return 1;
	}

	//Create SDL Window, Handle Error if it Fails
	SDL_Window* window = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}

	//Create SDL Renderer, Handle Error if it Fails
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	//Create an SDL surface and load .bmps on it, Handle Error if it Fails
	const std::string resPath = getResourcePath();
	SDL_Texture* background = loadTexture(resPath + "tileable_grass_00.png", renderer);
	SDL_Texture* foreground = loadTexture(resPath + "playerSprite.png", renderer);
	if(background == nullptr || foreground == nullptr) {
		cleanup(background, foreground, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	bool running = true;
	SDL_Event event;

	//Define Player x,y coordinates variables
	int pX = 0, pY = 0;

	//Calculate initial player position
	int fW, fH;
	SDL_QueryTexture(foreground, NULL, NULL, &fW, &fH);
	//pX = SCREEN_WIDTH / 2 - fW / 2;
	//pY = SCREEN_HEIGHT / 2 - fH / 2;
	pX = 0; pY = 0;

	//GAME LOOP
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_UP:
						pY = pY - 32;
					break;
					case SDLK_DOWN:
						pY = pY + 32;
					break;
					case SDLK_LEFT:
						pX = pX - 32;
					break;
					case SDLK_RIGHT:
						pX = pX + 32;
					break;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				//running = false;
			}
		}

		//Clear the Renderer, Place the Textures on it, then Display
		SDL_RenderClear(renderer);

		//Determine number of tiles necessary to fill the screen.
		int xTiles = SCREEN_WIDTH / TILE_SIZE;
		int yTiles = SCREEN_HEIGHT / TILE_SIZE;

		//Draw the tiles by calculating their positions
		for (int i = 0; i < xTiles * yTiles; i++) {
			int x = i % xTiles;
			int y = i / xTiles;
			renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}

		renderTexture(foreground, renderer, pX, pY);

		SDL_RenderPresent(renderer);
	}
	
	//POST GAME LOOP
	//Clean everything up and quit SDL
	cleanup(background, foreground, renderer, window);
	SDL_Quit();

	return 0;
} 
