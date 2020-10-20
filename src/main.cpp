#include "../headers/sdl2.h"

const int mapWidth = 24;
const int mapHeight = 24;

/**
 * main - entry point
 * 
 * @argc: argument count
 * @argv: list of arguments
 *
 * Retrun: exit status as int
 */
int main( int argc, char* argv[] )
{
    std::string path = "resources/maps/level_0.map";
    int** map = getMap( path.c_str() );
    //int numEnds = getDeadEnds( map );

    // Define windows & renderers
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
    // store window & renderers for easy destruction
    SDL_Instance instance = { mWindow, mRenderer };

    setup( &mWindow, &mRenderer );

    Character player;
    player.posX = 12; player.posY = 12;
    player.dirX = -1; player.dirY = 0;
    player.planeX = 0; player.planeY = 0.66;

    double time = 0;
    double oldTime = 0;

    int mouseX, mouseY;
    SDL_GetMouseState( &mouseX, &mouseY );
    bool progress = false;

    bool running = true;
    while( running )
    {
        SDL_Event e;
        while( SDL_PollEvent( &e ) )
        {
            if( e.type == SDL_QUIT )
                running = false;


            render( mRenderer, &player, map, &progress );

            oldTime = time;
            time = SDL_GetTicks();
            double frameTime = ( time - oldTime ) / 1000.0;

            int oldMouseX, rotDirection;
            switch ( e.type )
            {
                case SDL_KEYDOWN:
                    running = keyDown( &player, map );
                    break;
                case SDL_MOUSEMOTION:
                    oldMouseX = mouseX;
                    SDL_GetMouseState( &mouseX, &mouseY );
                    rotDirection = 0;
                    if( mouseX - oldMouseX > 0 ) rotDirection = 1;
                    if( mouseX - oldMouseX < 0 ) rotDirection = -1;
                    mouseMove( &player, rotDirection );
                    if( mouseX <= 20 || mouseX >= (GAME_WIDTH - 20) )
                        SDL_WarpMouseInWindow( mWindow, GAME_WIDTH / 2, GAME_HEIGHT / 2 );
                    if( mouseY <= 20 || mouseY >= (GAME_HEIGHT - 20) )
                        SDL_WarpMouseInWindow( mWindow, GAME_WIDTH / 2, GAME_HEIGHT / 2 );
                    break;
                default:
                    break;
            }
            if( ((int)player.posX == 22 && (int)player.posY == 22) && progress )
            {
                player.posX = 1;
                player.posY = 1;
                path[21]++;
                if( path[21] == '3' ) path[21] = '0';
                map = getMap( path.c_str() );
                progress = false;
            }
        }
    }

    close( &instance );

    return 0;
}

