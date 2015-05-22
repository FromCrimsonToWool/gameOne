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
}

//Logic Update
void Core::update(const float DELTA_T) {
	//TODO: Determine how updating game logic should work.
}