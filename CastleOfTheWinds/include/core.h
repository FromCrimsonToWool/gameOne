#ifndef CORE_H
#define CORE_H

//Define Shell so Core realizes it is the outer layer of the game.
class Shell;

//SDL Include
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//User Include
#include "include/shell.h"

class Core {
	private:
		Shell* display;
		SDL_Window* app;
		SDL_Renderer* renderer;

		bool gameLoop;
	public:
		/**Constructors**/
		Core();
		Core(SDL_Window* a, SDL_Renderer* r);

		/**Accessors & Mutators**/
		//Tells the Core who the Shell is.
		void setShell(Shell* s) { display = s; }
		//Checks if the Core is running and thus by extension the game itself.
		bool isRunning();
		//Updates the Game Logic by time change DELTA_T.
		void update(const float DELTA_T);
};

#endif //CORE_H INCLUDED