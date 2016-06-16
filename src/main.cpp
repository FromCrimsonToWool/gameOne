#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <include/res_path.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
//const std::string = getResourcePath("Castle_Of_The_Winds-Universal");

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gCharacterSprite = NULL;

bool init(){
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags )){
                printf( "SDL_image  could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            } else {
                gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
        }
    }

    return success;
}

bool loadMedia(){

    SDL_Rect gSpriteClips[ 4 ];

    bool success = true;
    gCharacterSprite = loadSurface( getResourcePath() + "cotwsprites02.gif" );

    if( gCharacterSprite == NULL ){
        printf( "Failed to load character sprite image.\n" );
        success = false;
    } else {
        gSpriteClips[ 0 ].x = 32 * 6;
        gSpriteClips[ 0 ].y = 32 * 16;
        gSpriteClips[ 0 ].w = 32;
        gSpriteClips[ 0 ].h = 32;
    }

    return success;
}

SDL_Surface* loadSurface( std::string path ){
   SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ){
        printf( "Unable to load image %s!  SDL_image Error:  %s\n", path.c_str(), IMG_GetError() );
    } else {
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
        if( optimizedSurface == NULL ){
            printf( "Unable to optimize image %s!  SDL_Error:  %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

void close(){
    SDL_FreeSurface( gCharacterSprite );
    gCharacterSprite = NULL;

    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int, char**){
    if( !init() ){
        printf( "Failed to initialize!\n" );
    } else {
        if( !loadMedia() ){
            printf( "Failed to load media!\n" );
        } else {
            bool quit = false;
            SDL_Event e;

            while(!quit){
               while( SDL_PollEvent( &e ) != 0 ){
                  if( e.type == SDL_QUIT ){ quit = true; }
               }

                SDL_BlitSurface( gCharacterSprite, NULL, gScreenSurface, NULL );
                SDL_UpdateWindowSurface( gWindow );
            }
        }
    }

    close();
    return 0;
}
