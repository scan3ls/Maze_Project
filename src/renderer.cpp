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
    // draw anchovy
    SDL_Texture* anch = NULL;
    SDL_Rect rendQuad = {0,0,0,0};
    if( drawAnchovy(renderer, &anch, &rendQuad, player) ) SDL_RenderCopy( renderer, anch, NULL, &rendQuad );

    // Set Default Background Color
    SDL_SetRenderDrawColor( renderer,255,255,255,0 );

    SDL_RenderPresent( renderer );
}

bool drawAnchovy( SDL_Renderer* renderer, SDL_Texture** anch, SDL_Rect* rect, bool visable )
{
    if( visable == false ) return false;
    if( rect->x >= GAME_WIDTH - rect->w ) return false;
  
    rect->y = GAME_HEIGHT / 2;
    SDL_RenderCopy( renderer, *anch, NULL, rect );
    return true;
}
