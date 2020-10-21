#include "../headers/sdl2.h"
#define VIEW displays[0] // main game view
#define MINIMAP displays[1] // minimap view
#define SHEET displays[2] // view below minimap

/**
 * raycaster - draws graphics to renderer
 *
 * @player: player character struct
 * @displays: list of displays as ViewPorts on the window
 * @level: current level data
 */ 

void raycaster( Character* player, ViewPort* displays[], Level* level)
{
    SDL_Texture* anch = NULL;
    SDL_Rect rect = {0,0,0,0};
    SDL_Surface* loadedSurface = IMG_Load( "resources/images/Anchovy.bmp" );
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format,0,0xFF,0xFF) );
    bool visable = false;
    int start = 0;
    rect.w = loadedSurface->w;
    rect.h = loadedSurface->h;
    anch = SDL_CreateTextureFromSurface( VIEW->renderer, loadedSurface );
    SDL_FreeSurface( loadedSurface );

    for( int x = 0; x < VIEW->width; x++ ) // raycaster
    {
        double cameraX = 2 * x / double(VIEW->width) - 1;
        double rayDirX = player->dirX + player->planeX * cameraX;
        double rayDirY = player->dirY + player->planeY * cameraX;

        int mapX = int(player->posX);
        int mapY = int(player->posY);

        double sideDistX, sideDistY;

        double deltaDistX = std::abs(1 / rayDirX );
        double deltaDistY = std::abs(1 / rayDirY );
        double perpWallDist;

        int stepX, stepY;
        int hit = 0;
        int side;

        if( rayDirX < 0 )
        {
            stepX = -1;
            sideDistX = ( player->posX - mapX ) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = ( mapX + 1.0 - player->posX ) * deltaDistX;
        }

        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (player->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
        }
        
        while (hit == 0) // DDA
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if(level->map[mapX][mapY] > 0)
            {
                hit = 1;
            }
            else if( ( mapX == level->AnchovyPosX && mapY == level->AnchovyPosY ) && !(level->progress) )
            {
                start = x;
                visable = true;
            }

        } // end DDA

        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if( side == 0 ) perpWallDist = (mapX - player->posX + (1 - stepX) / 2) / rayDirX;
        else            perpWallDist = (mapY - player->posY + (1 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        int lineHeight = (int)(VIEW->height / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + VIEW->height / 2;
        if( drawStart < 0 ) drawStart = 0;
        int drawEnd = lineHeight / 2 + VIEW->height / 2;
        if( drawEnd >= VIEW->height ) drawEnd = VIEW->height - 1;

        // Texture calcs
        bool isWall = false;
        if( level->map[mapX][mapY] > 0 ) isWall = true;

        double wallX;
        if( side == 0 ) wallX = player->posY + perpWallDist * rayDirY;
        else            wallX = player->posX + perpWallDist * rayDirX;
        wallX -= floor( ( wallX ) );
        
        // Draw main display
        drawDispaly( VIEW, x, drawStart, drawEnd, level->map, side, mapX, mapY );
        // Draw miniMap
        drawMap( MINIMAP, level->map, player );
        // Draw charSheet
        //drawSheet( SHEET, player );

    } // end raycaster

    // Draw Anchovy
    rect.x = start;
    double dist = sqrt( pow( level->AnchovyPosX - player->posX, 2 ) + pow( level->AnchovyPosY - player->posY, 2) );
    if( (int)dist == 0 )
    {
        visable = false;
        level->progress = true;
    }
    rect.w = rect.w * std::abs( 5 / dist );
    rect.h = rect.h * std::abs( 5 / dist );
    drawAnchovy( VIEW->renderer, &anch, &rect, visable );
    if( level->progress )
    {
        level->map[22][23] = 3;
        level->map[23][22] = 3;
    }
    SDL_DestroyTexture( anch );
}

/**
 * wallColor - choose wall color
 * 
 * @x: value of a given position x,y cordinate in a map matrix
 * @side: flag to add shadow to wall
 * @rederer: rendering engine used
 */

void wallColor( int x, int side, SDL_Renderer* renderer )
{
    int r=0,b=0,g=0,a=255;
    switch( x )
    {
        case 2:
            r=255,b=0, g=0;
            if( side == 1 )
                r/=2,b/=2,g/=2;
            break; //red
        case 3:
            r=0,g=255,b=0,a=0;     
            if( side == 1 )
                r/=2,b/=2,g/=2;
            break; //green
        case 1:
            r=0,g=0,b=255;
            if( side == 1 )
                r/=2,b/=2,g/=2;                    
            break; //blue
        case 4:
            r=255,g=255,b=255;
            if( side == 1 )
                r/=2,b/=2,g/=2;                    
            break; //white
        default:
            break;
    }
    SDL_SetRenderDrawColor(renderer,r,g,b,a);
}

/**
 * drawDisplay - Draws main game display
 * 
 * @view: display to draw to on window
 * @x: relative x position in view
 * @drawStart: begining relative y position of wall line in view
 * @drawEnd: Ending relative y position on wall line in view
 * @map: level to render
 * @mapX: x position in map
 * @mapY: y position in map
 */

void drawDispaly( ViewPort* view, int x, int drawStart, int drawEnd, int** map, int side, int mapX, int mapY )
{
    // draw sky
    SDL_SetRenderDrawColor(view->renderer,135,206,235,255);  //Sky blue
    SDL_RenderDrawLine(view->renderer,x+view->posX,0,x+view->posX,drawStart);
    
    //choose wall color
    //draw walls
    int height = drawEnd - drawStart;
    wallColor( map[mapX][mapY], side, view->renderer );
    SDL_RenderDrawLine(view->renderer,x+view->posX,drawStart,x+view->posX,drawEnd);
    
    //draw ground
    SDL_SetRenderDrawColor(view->renderer,105,139,105,255);  // Dark Sea Green
    SDL_RenderDrawLine(view->renderer,x+view->posX,drawEnd,x+view->posX,view->height);
}

/**
 * drawMap - draws minimap of the level
 * 
 * @view: display to draw to on window
 * @map: level to render
 * @player: player character struct
 */

void drawMap( ViewPort* view, int** map, Character* player )
{
    int sqSize = 64;
    int startY = 2 * sqSize;
    int startX = GAME_WIDTH + startY;
    int color = 0;
    int mapX = (int)player->posX;
    int mapY = (int)player->posY;

    // Draw Player
    SDL_Rect rect = { startX, startY, sqSize, sqSize };
    SDL_SetRenderDrawColor( view->renderer,255,255,0,0 ); //yellow
    SDL_RenderFillRect( view->renderer, &rect );
    // Draw Facing Vector
    SDL_SetRenderDrawColor( view->renderer,255,0,0,0 );
    SDL_RenderDrawLine( view->renderer, startX + 32, startY + 32, (startX + 32) + (player->dirX * sqSize), (startY + 32) + (player->dirY * sqSize) );
    SDL_SetRenderDrawColor( view->renderer,0,0,0,0 ); // Black

    SDL_Rect left, right, up, down;
    SDL_Rect crn1,  crn2, crn3, crn4;

    int x = startX + -1 * sqSize;
    int y = startY;
    left = {x, y, sqSize, sqSize};
    y = startY - sqSize;
    crn1 = {x,y,sqSize,sqSize};

    x = startX + sqSize;
    right = {x, startY, sqSize, sqSize};
    crn2 = {x,y,sqSize,sqSize};
    
    x = startX;
    y = startY + -1 * sqSize;
    up = {x,y,sqSize,sqSize};

    y = startY + sqSize;
    down = {x,y,sqSize,sqSize};
    x -= sqSize;
    crn3 = {x,y,sqSize,sqSize};
    x += 2*sqSize;
    crn4 = {x,y,sqSize,sqSize};

    if( 0 < mapX < 23 && 0 < mapY < 23)
    {
        if( map[mapX - 1][mapY] )
            SDL_RenderDrawRect( view->renderer, &left );
        if( map[mapX + 1][mapY] )
            SDL_RenderDrawRect( view->renderer, &right );
        if( map[mapX][mapY - 1] )
            SDL_RenderDrawRect( view->renderer, &up );
        if( map[mapX][mapY + 1] )
            SDL_RenderDrawRect( view->renderer, &down );
    }
    if( 1 < mapX < 22 && 1 < mapY < 22 )
    {
        if( map[mapX - 1][mapY - 1] )
            SDL_RenderDrawRect( view->renderer, &crn1 );
        if( map[mapX + 1][mapY - 1] )
            SDL_RenderDrawRect( view->renderer, &crn2 );
        if( map[mapX - 1][mapY + 1] )
            SDL_RenderDrawRect( view->renderer, &crn3 );
        if( map[mapX + 1][mapY + 1] )
            SDL_RenderDrawRect( view->renderer, &crn4 );
    }
}

/**
 * drawSheet - draw an info box on the screen
 * 
 * @view: display to draw to on window
 * @player: player character struct
 */

void drawSheet( ViewPort* view, Character* player )
{
    SDL_Rect border;
    border.h =  view->height;
    border.w = view->width;
    border.x = view->posX;
    border.y = view->posY;

    SDL_SetRenderDrawColor( view->renderer,0,0,0,0 );
    SDL_RenderDrawRect( view->renderer, &border );
}