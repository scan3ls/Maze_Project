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

#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720
#define GAME_WIDTH      960
#define GAME_HEIGHT     SCREEN_HEIGHT
#define MAP_SIZE        SCREEN_WIDTH - GAME_WIDTH //miniMap size

typedef struct SDL_Instance
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
} SDL_Instance;

typedef struct character
{
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
} Character;

typedef struct viewport
{
    SDL_Renderer* renderer;
    int width, height;
    int posX, posY; //inital starting position
} ViewPort;

/******************/
/*   Functions    */
/******************/

/* main */

/* utilites.cpp */
void setup( SDL_Window** window, SDL_Renderer** renderer );
void close( SDL_Instance* instance );
bool run( SDL_Event e );

/* controlls.cpp */
bool keyDown( Character* player, int** map );
void mouseMove( Character* player, int rotDirection );

/* getMap.cpp */
int** getMap( std::string path );
int getDeadEnds( int** map );

/* renderer.cpp */
void render( SDL_Renderer* renderer, Character* player, int** map );
bool drawAnchovy( SDL_Renderer* renderer, SDL_Texture** anch, SDL_Rect* rect, bool visable );

/* raycaster.cpp */
void raycaster( Character* player, ViewPort* displays[], int** map );
void wallColor( int x, int side, SDL_Renderer* renderer );
void drawDispaly( ViewPort* view, int x, int drawStart, int drawEnd, int** map, int side, int mapX, int mapY );
void drawMap( ViewPort* view, int** map, Character* player );
void drawSheet( ViewPort* view, Character* Player );

#endif // _SDL2_H_