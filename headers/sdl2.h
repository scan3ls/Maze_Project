#ifndef _SDL2_H_
#define _SDL2_H_

#include "../dependencies/x64/include/SDL2/SDL.h"
#include "../dependencies/x64/include/SDL2/SDL_image.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdlib.h>

#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720
#define GAME_WIDTH      SCREEN_WIDTH - 320
#define GAME_HEIGHT     SCREEN_HEIGHT
#define MAP_SIZE        SCREEN_WIDTH - ( GAME_WIDTH )  //miniMap size

/**
 *  SDL_Instance - container for an instance of SDL.
 *  Hold values for SDL_Window and SDL_Renderer
 * 
 * @window: SDL_Window
 * @renderer: SDL_Renderer
 */
typedef struct SDL_Instance
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
} SDL_Instance;

/**
 * Character - Container for character data
 * 
 * @posX: X position of the character on the map
 * @posY: Y position of the character on the map
 * @dirX: X component of the direction vector
 * @dirY: Y component of the direction vector
 * @planeX: X component of the camera plane
 * @planeY: Y component of the camera plane
 */
typedef struct character
{
    double  posX, posY;
    double  dirX, dirY;
    double  planeX, planeY;
} Character;

/**
 * ViewPort - Define portion of a window to display a specific element
 * 
 * @renderer: SDL_Renderer of the SDL_Instance used
 * @width: width of the view display
 * @height: height of the view display
 * @posX: X position of the top-left most pixel of the view display
 * @posY: Y position of the top-left most pixel of the view display
 */
typedef struct viewport
{
    SDL_Renderer* renderer;
    int           width, height;
    int           posX, posY;
} ViewPort;

/**
 * Level - Container for level data
 * 
 * @map: loaded map as a 2D int array
 * @AnchovyPosX: Anchovy position as the second indexing element of the map
 * @AnchovyPosY: Anchovy position as the first indexing element of the map
 * @progress: Flag for the ability to progress to the next level
 */
typedef struct Level
{
    int**   map;
    int     AnchovyPosX;
    int     AnchovyPosY;
    bool    progress;
} Level;

/******************/
/*   Functions    */
/******************/

/******************/
/*  utilites.cpp  */
/******************/


void setup( SDL_Window** window, SDL_Renderer** renderer );
void close( SDL_Instance* instance );
bool run( SDL_Event e );


/******************/
/*  controlls.cpp */
/******************/

bool keyDown( Character* player, int** map );
void mouseMove( Character* player, int rotDirection );


/******************/
/*   parser.cpp   */
/******************/

int** getMap( std::string path );
int* getAnchovySpawn( int** map );
bool isWall( int num );
bool isDeadEnd( int** map, int row, int column );

/******************/
/*  renderer.cpp  */
/******************/

void render( SDL_Renderer* renderer, Character* player, Level* level );
bool drawAnchovy( SDL_Renderer* renderer, SDL_Texture** anch, SDL_Rect* rect, bool visable );

/******************/
/* raycaster.cpp  */
/******************/

void raycaster( Character* player, ViewPort* displays[], Level* level );
void wallColor( int x, int side, SDL_Renderer* renderer );
void drawDispaly( ViewPort* view, int x, int drawStart, int drawEnd, int** map, int side, int mapX, int mapY );
void drawMap( ViewPort* view, int** map, Character* player );
void drawSheet( ViewPort* view, Character* Player );

#endif // _SDL2_H_