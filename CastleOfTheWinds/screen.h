#ifndef SCREEN_H
#define SCREEN_H

class Shell;

//Standard Include
#include <iostream>
#include <fstream>
//SDL Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//User Include
#include "shell.h"

class Screen {
	protected:
		Shell* display;
		SDL_Window* app;
		SDL_Renderer* renderer;

	public:
		//Constructors
		Screen();
		Screen(SDL_Window* a, SDL_Renderer* r, Shell* s);

		//Accessors & Mutators
		void setShell(Shell* s);
		Shell* getShell();

		//Screen Functions
		virtual void hideScreen() = 0;
		virtual void showScreen() = 0;
};

#endif //SCREEN_H INCLUDED