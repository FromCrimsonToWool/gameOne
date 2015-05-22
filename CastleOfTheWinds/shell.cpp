#include "shell.h"
#include "core.h"

//Default Constructor, Unused
Shell::Shell() {
	//Do Nothing.
}

//Standard Constructor
Shell::Shell(SDL_Window* a, SDL_Renderer* r) {
	app = a;
	renderer = r;
}

void Shell::draw(const float INTERPOLATION) {
	//TODO: Determine how drawing gui should work.
}