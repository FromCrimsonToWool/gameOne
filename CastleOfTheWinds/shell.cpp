//Standard Include
#include <string>
//SDL Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//User Include
#include "shell.h"
#include "core.h"
#include "include/cleanup.h"
#include "include/res_path.h"
#include "include/jpfSDLTexture.h"

//Default Constructor, Unused
Shell::Shell() {
	//Do Nothing.
}

//Standard Constructor
Shell::Shell(SDL_Window* a, SDL_Renderer* r) {
	app = a;
	renderer = r;
	std::string resPath = getResourcePath();

	//Create an SDL surface and load .bmps on it, Handle Error if it Fails
	SDL_Texture* background = loadTexture(resPath + "tileable_grass_00.png", renderer);
	SDL_Texture* foreground = loadTexture(resPath + "playerSprite.png", renderer);
	if (background == nullptr || foreground == nullptr) {
		cleanup(background, foreground, renderer, app);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
}

int Shell::initCheck() {
	if (background == nullptr || foreground == nullptr) {
		return false;
	} else {
		return true;
	}
}

void Shell::draw(const float INTERPOLATION) {
	//TODO: Determine how drawing gui should work.

	//Define Player x,y coordinates variables
	int pX = 0, pY = 0;

	//Calculate initial player position
	int fW, fH;
	SDL_QueryTexture(foreground, NULL, NULL, &fW, &fH);
	//pX = SCREEN_WIDTH / 2 - fW / 2;
	//pY = SCREEN_HEIGHT / 2 - fH / 2;
	pX = 0; pY = 0;


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

	
}