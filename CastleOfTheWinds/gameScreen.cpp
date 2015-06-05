#include "gameScreen.h"
#include "shell.h"

//Default Constructor, Unused
GameScreen::GameScreen() {
	//Do Nothing.
}

GameScreen::GameScreen(Shell* s) : Screen(s) {
	background = loadTexture(resPath + "tileable_grass_00.png", renderer);
	foreground = loadTexture(resPath + "playerSprite.png", renderer);
}