/**
PROJECT GAMMA: Castle of the Winds Redux (Julien)
@author Julien Fernandes
@version 0.01b Wherein The Core and Shell Are Made
**/

//Standard Include
#include <iostream>
#include <fstream>
#include <string>
//SDL Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//User Include
#include "include/core.h"
#include "include/shell.h"
#include "include/res_path.h"
#include "include/cleanup.h"
#include "include/textFileParser.h"
#include "include/logSDLError.h"
#include "include/jpfSDLTexture.h"

//DEBUG variable. SHOULD NOT BE IN RELEASE.
int debug;

/** Initial Settings Variables
Variables that the main function needs access to in order to launch the game 
with the correct settings loaded from disk. These variables should be set by
the settingsRead() function.
**/
int screenX, screenY; //Stores read values for screen X and Y dimensions.

/** Temporary Settings Variables
Temporary variables that define some contants the game uses. SHOULD NOT BE 
IN RELEASE. These values should eventually come from the Initial Settings 
Variables or be defined constants.
**/
const int SCREEN_WIDTH = 1600; //Window X Dimension.
const int SCREEN_HEIGHT = 928; //Window Y Dimension.
const int TILE_SIZE = 32; //The dimensions in pixels of one tile in the game.

//Reads initial settings used for when the game is launched. This includes things
//like what dimensions the game window should be, whether it should be fullscreen
//or not etc. 
void settingsRead() {
	//TODO: Implement reading from a settings.txt file which is included 
	//in the main directory.
}

int main(int argc, char** argv) {
	/**PRE GAME LOOP**/
	//SDL Video Subsystem Initialization
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logSDLError(std::cout, "SDL_INIT");
		return 1;
	}

	//SDL Image Subsystem Initialization
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_INIT");
		SDL_Quit();
		return 1;
	}

	//SDL Window Creation
	SDL_Window* app = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//Error Handling
	if(app == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}

	//SDL Renderer Creation
	SDL_Renderer* renderer = SDL_CreateRenderer(app, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//Error Handling
	if (renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		cleanup(app);
		SDL_Quit();
		return 1;
	}

	/**Game Creation
	Sets up the game world as far as the application is concerned. The Core handles the internal specifics
	of the game and its logic while the Shell handles the Graphical Interface and interaction with the User.
	**/
	static Shell display(app, renderer);
	static Core logic(app, renderer);
	logic.setShell(&display);
	display.setCore(&logic);

	//Create an SDL surface and load .bmps on it, Handle Error if it Fails
	const std::string resPath = getResourcePath();
	SDL_Texture* background = loadTexture(resPath + "tileable_grass_00.png", renderer);
	SDL_Texture* foreground = loadTexture(resPath + "playerSprite.png", renderer);
	if(background == nullptr || foreground == nullptr) {
		cleanup(background, foreground, renderer, app);
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

	/**GAME LOOP**/
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_UP:
						if (pY >= 32) {
							pY = pY - 32;
						}
					break;
					case SDLK_DOWN:
						if (pY <= SCREEN_HEIGHT - (TILE_SIZE * 2)) {
							pY = pY + 32;
						}
					break;
					case SDLK_LEFT:
						if (pX >= TILE_SIZE) {
							pX = pX - 32;
						}
					break;
					case SDLK_RIGHT:
						if (pX <= SCREEN_WIDTH - (TILE_SIZE * 2)) {
							pX = pX + 32;
						}
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
	
	/**POST GAME LOOP**/
	//Clean everything up and quit SDL
	cleanup(background, foreground, renderer, app);
	SDL_Quit();

	return 0;
} 
