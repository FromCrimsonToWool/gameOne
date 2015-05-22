#ifndef SHELL_H
#define SHELL_H

//Define Core so Shell realizes it is the inner layer of the game.
class Core;

//SDL Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//User Include
#include "include/core.h"

class Shell {
	private: 
		Core* logic;
		SDL_Window* app;
		SDL_Renderer* renderer;

	public:
		/**Constructors**/
		Shell(); 
		Shell(SDL_Window* a, SDL_Renderer* r);

		/**Accessors & Mutators**/
		//Tells the Shell who the Core is.
		void setCore(Core* c) { logic = c; }
		//Updates the GUI taking into consideration INTERPOLATION
		void draw(const float INTERPOLATION);
};

#endif //SHELL_H INCLUDED