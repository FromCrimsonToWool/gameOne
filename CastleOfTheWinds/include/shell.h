#ifndef SHELL_H
#define SHELL_H

//Define Core so Shell realizes it is the inner layer of the game.
class Core;
class GameScreen;

//Standard Include
#include <string>
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

		const std::string resPath;

		//Game Screens
		GameScreen* game;
	public:
		/**Constructors**/
		Shell(); 
		Shell(SDL_Window* a, SDL_Renderer* r);

		/**Accessors & Mutators**/
		//Tells the Shell who the Core is.
		void setCore(Core* c) { logic = c; }

		/**Utility Functions**/
		//Allows the main function to gracefully error out if something failed to initilize in the Shell constructor.
		bool initCheck();

		/**Draw Function**/
		//Updates the GUI taking into consideration INTERPOLATION
		void draw(const float INTERPOLATION);
};

#endif //SHELL_H INCLUDED