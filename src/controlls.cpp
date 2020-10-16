#include "../headers/sdl2.h"

bool keyDown( Character* player, int** map )
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    double moveSpeed = 0.03 * 3.0;
    double rotSpeed = 0.03 * 1.0;
    //move forward
    if( currentKeyStates[ SDL_SCANCODE_W ] )
    {
        if(map[int(player->posX + player->dirX * moveSpeed)][int(player->posY)] == false) player->posX += player->dirX * moveSpeed;
        if(map[int(player->posX)][int(player->posY + player->dirY * moveSpeed)] == false) player->posY += player->dirY * moveSpeed;
    }
    //move back
    if( currentKeyStates[ SDL_SCANCODE_S ] )
    {
        if(map[int(player->posX - player->dirX * moveSpeed)][int(player->posY)] == false) player->posX -= player->dirX * moveSpeed;
        if(map[int(player->posX)][int(player->posY - player->dirY * moveSpeed)] == false) player->posY -= player->dirY * moveSpeed;
    }
    if( currentKeyStates[ SDL_SCANCODE_D ] )
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = player->dirX;
        player->dirX = player->dirX * cos(-rotSpeed) - player->dirY * sin(-rotSpeed);
        player->dirY = oldDirX * sin(-rotSpeed) + player->dirY * cos(-rotSpeed);
        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
        player->planeY = oldPlaneX * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);
    }
    //rotate left
    if( currentKeyStates[ SDL_SCANCODE_A ] )
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = player->dirX;
        player->dirX = player->dirX * cos(rotSpeed) - player->dirY * sin(rotSpeed);
        player->dirY = oldDirX * sin(rotSpeed) + player->dirY * cos(rotSpeed);
        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
        player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);
    }

    if( currentKeyStates[ SDL_SCANCODE_ESCAPE ] )
        return false;

    return true;
}

void mouseMove( Character* player, int rotDirection )
{
    double rotSpeed = 0.03 * 0.75;

        //rotate right
    if( rotDirection > 0 )
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = player->dirX;
        player->dirX = player->dirX * cos(-rotSpeed) - player->dirY * sin(-rotSpeed);
        player->dirY = oldDirX * sin(-rotSpeed) + player->dirY * cos(-rotSpeed);
        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
        player->planeY = oldPlaneX * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);
    }
    //rotate left
    if( rotDirection < 0 )
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = player->dirX;
        player->dirX = player->dirX * cos(rotSpeed) - player->dirY * sin(rotSpeed);
        player->dirY = oldDirX * sin(rotSpeed) + player->dirY * cos(rotSpeed);
        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
        player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);
    }
}