#include "../headers/sdl2.h"

/**
 * render - main rendering controller.
 * Creates viewports, calls the raycasting,
 * and updates the screen.
 * 
 * @renderer: rendering engine
 * @player: player character struct
 * @map: level to render
 * @found: progress flag to next level
 */

void render( SDL_Renderer* renderer, Character* player, int** map, bool* found )
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
    raycaster( player, displays, map, found );
    // draw anchovy

    // Set Default Background Color
    SDL_SetRenderDrawColor( renderer,255,255,255,0 );

    SDL_RenderPresent( renderer );
}

/**
 * drawAnchovy - draw Anchovy sprite on the screen in correct position
 * 
 * @renderer: rendering engine
 * @anch: pointer to anchovy texture
 * @rect: pointer to rectangle
 * @visable: flag for line of sight
 * 
 * Return: bool flag if sprite should be on screen
 */
bool drawAnchovy( SDL_Renderer* renderer, SDL_Texture** anch, SDL_Rect* rect, bool visable )
{
    if( visable == false ) return false;
    if( rect->x >= GAME_WIDTH - rect->w ) return false;
  
    rect->y = GAME_HEIGHT / 2;
    SDL_RenderCopy( renderer, *anch, NULL, rect );
    return true;
}
