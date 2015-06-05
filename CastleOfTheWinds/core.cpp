#include "core.h"
#include "shell.h"

//Default Constructor, Unused
Core::Core() {
	//Do Nothing.
}

//Standard Constructor
Core::Core(SDL_Window* a, SDL_Renderer* r) {
	app = a;
	renderer = r;
	gameLoop = true;
}

bool isRunning() {
	return gameLoop;
}

//Logic Update
void Core::update(const float DELTA_T) {
	//Event Processing
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			gameLoop = false;
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
}