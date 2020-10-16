#include "../headers/sdl2.h"

void render( SDL_Renderer* renderer, Character* player, int** map )
{

    ViewPort view =
    {
        renderer,
        GAME_WIDTH, GAME_HEIGHT,
        0, 0 
    };
    
    ViewPort miniMap =
    {
        renderer,
        MAP_SIZE, MAP_SIZE,
        GAME_WIDTH, 0
    };

    ViewPort charSheet = 
    {
        renderer,
        MAP_SIZE, SCREEN_HEIGHT - ( MAP_SIZE ),
        GAME_WIDTH, MAP_SIZE
    };

    ViewPort* displays[3] = { &view, &miniMap, &charSheet };
    SDL_RenderClear( renderer );
    // draw main view
    raycaster( player, displays, map );
    // Set Default Background Color
    SDL_SetRenderDrawColor( renderer,255,255,255,0 );

    SDL_RenderPresent( renderer );
}

