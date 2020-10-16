#include "../headers/sdl2.h"

/**
 * setup - setup window and renderer for display
 * 
 */

void setup( SDL_Window** window, SDL_Renderer** renderer )
{
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_JPG );
    

    *window = SDL_CreateWindow(
        "TITLE",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_MOUSE_FOCUS
    );

    *renderer = SDL_CreateRenderer(
        *window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    
    SDL_ShowCursor( SDL_DISABLE );
    SDL_WarpMouseInWindow( *window, GAME_WIDTH / 2, GAME_HEIGHT / 2 );
}

/**
 * close - SDL clean up
 */
void close( SDL_Instance* instance )
{

    SDL_DestroyRenderer( instance->renderer );
    SDL_DestroyWindow( instance->window );
    
    SDL_ShowCursor( SDL_ENABLE );

    IMG_Quit();
    SDL_Quit();
}

/**
 * running - gets/execute user commands 
 * 
 */
bool run(SDL_Event e)
{
    // SDL_Event e;
    while( SDL_PollEvent( &e ) )
    {
        if( e.type == SDL_QUIT )
            return false;
    }
    return true;
}