#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <include/res_path.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
//const std::string = getResourcePath("Castle_Of_The_Winds-Universal");

class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( std::string path );

        //Deallocates texture
        void free();

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//sprites
SDL_Rect gSpriteClips[ 4 ];
LTexture gSpriteSheetTexture;

LTexture::LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mWidth = 0;
}

LTexture::~LTexture(){
    free();
}

bool LTexture::loadFromFile( std::string path ){
    //Get rid of pre-existing texture
    free();

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ));
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

        if( newTexture == NULL ){
            printf( "Unable to create texture from %s!  SDL Error: %s\n", path.c_str(), SDL_GetError() );
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface( loadedSurface );
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free(){
    if( mTexture != NULL ){
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render( int x, int y, SDL_Rect* clip ){
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    if( clip != NULL ){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth(){
    return mWidth;
}

int LTexture::getHeight(){
    return mHeight;
}

bool init(){
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )){
            printf( "Warning:  Linear texture filtering not enabled!" );
        }

        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL ){
                printf( "Renderer could not be created!  SDL error:  %s\n", SDL_GetError() );
                success = false;
            } else {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags )){
                    printf( "SDL_image  could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia(){

    bool success = true;
    if( !gSpriteSheetTexture.loadFromFile( getResourcePath() + "cotwsprites02.gif" )){
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    } else {
        gSpriteClips[ 0 ].x = 32 * 6;
        gSpriteClips[ 0 ].y = 32 * 16;
        gSpriteClips[ 0 ].w = 32;
        gSpriteClips[ 0 ].h = 32;

        gSpriteClips[ 1 ].x = 32 * 7;
        gSpriteClips[ 1 ].y = 32 * 16;
        gSpriteClips[ 1 ].w = 32;
        gSpriteClips[ 1 ].h = 32;

        gSpriteClips[ 2 ].x = 32 * 7;
        gSpriteClips[ 2 ].y = 32 * 18;
        gSpriteClips[ 2 ].w = 32;
        gSpriteClips[ 2 ].h = 32;

        gSpriteClips[ 3 ].x = 32 * 2;
        gSpriteClips[ 3 ].y = 32 * 11;
        gSpriteClips[ 3 ].w = 32;
        gSpriteClips[ 3 ].h = 32;

    }

    return success;
}

void close(){
    gSpriteSheetTexture.free();

    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

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

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                gSpriteSheetTexture.render( 0, 0, &gSpriteClips[ 0 ] );
                gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );
                gSpriteSheetTexture.render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );
                gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );

                SDL_RenderPresent( gRenderer );
            }
        }
    }

    close();
    return 0;
}
