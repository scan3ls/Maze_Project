#include "../headers/sdl2.h"
using namespace std;

/**
 * getMap - create map from file
 * @path: path to map file
 * 
 * Return: map file as int matrix
 */
int** getMap( string path )
{
    ifstream myFile ( path.c_str() );
    string line;
    int** map = 0;
    map = new int*[24];

    if (myFile.is_open())
    {
        for(int h = 0; h < 24; h++)
        {
            map[h] = new int[24];
            getline(myFile, line);
            int c = 0, index = 0;
            for (; line[c] != '\0'; c++, index++)
                map[h][index] = line[c] - '0';
        }
    }
    else
    {
        return NULL;
    }
    
    myFile.close();
    return map;
}

/**
 * getAnchovySpawn - get Anchovy spawn location
 * 
 * Return - list of matrix indecies
 */
int* getAnchovySpawn( int** map )
{
    int counter = 0;
    int row = 1;
    int column = 1;
    int up, down, left, right;
    int* pos = (int*)malloc( sizeof( int ) * 2 );

    while( row < 23 )
    {
        for( column = 1; column < 23; column++ )
        {
            if( isWall( map[row][column] ) ) continue;
            // Choosing third dead end to spawn anchovy
            if( isDeadEnd( map, row, column ) ) 
            {
                counter++;
                if( counter == 3 )
                {
                    pos[0] = row;
                    pos[1] = column;
                    row = 30;
                    column = 30;
                }
            }
        }
        row++;
    }
    return pos;
}

/**
 * isWall - check if num represents a wall
 * @num: int to check
 * 
 * Return: True if is wall else False
 */
bool isWall( int num )
{
    if( num > 0 ) return true;
    
    return false;
}

/**
 * isDeadEnd - check if position in map at given 
 *             row & column is a dead end
 * @map: 2d array
 * @row: row of the 2d array
 * @column: column of the 2d array
 * 
 * Return: True if values at cardinal points around 
 *         the position is three else False
 */
bool isDeadEnd( int** map, int row, int column )
{
    int up, down, left, right;

    up = map[row - 1][column];
    down = map[row + 1][column];
    left = map[row][column - 1];
    right = map[row][column + 1];
    int sum = up + down + left + right;

    if( sum == 3 ) return true;

    return false;
}