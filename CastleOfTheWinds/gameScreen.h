#ifndef GAMESCREEN_H
#define GAMESCREEN_H

class Shell;

//SDL Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//User Include
#include "screen.h"

class GameScreen : public Screen {
	private:
		SDL_Texture* background;
		SDL_Texture* foreground;
	
	public:
		GameScreen();
		GameScreen(Shell* s);
};

#endif //GAMESCREEN_H INCLUDED