/**
PROJECT GAMMA: Castle of the Winds Redux (Julien)
@author Julien Fernandes
@version 0.01cALPHA Wherein We Write Very Boring Boilerplate
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

	display.initCheck();

	/**Clock & Time Creation**/
	//TODO: Figure out how to handle time in this game. Should be relatively simple.
	const float DELTA_T = 0.0f;
	const float INTERPOLATION = 0.0f;

	/**GAME LOOP**/
	while (logic.isRunning()) {
		//Clear the application window for new update and drawing.
		SDL_RenderClear(renderer);

		/**Logic Update**/
		//Update the game logic in DELTA_T increments for the Core. 
		logic.update(DELTA_T);
		
		/**Display Draw**/
		//Update the game display taking INTERPOLATION into account.
		display.draw(INTERPOLATION);

		/**Update Renderer**/
		//Update the SDL Renderer to display to the player.
		SDL_RenderPresent(renderer);
	}
	
	/**POST GAME LOOP**/
	//Clean everything up and quit SDL.
	cleanup(renderer, app);
	SDL_Quit();

	//Upon exit from the game loop close the program successfully.
	return EXIT_SUCCESS;
} 
