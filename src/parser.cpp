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
 * getDeadEnds - get Dead ends for possible anchovy location
 * 
 * Return - list of matrix indecies
 */

int getDeadEnds( int** map )
{
    int ends = 0;
    int row = 1;
    int column = 1;
    int up, down, left, right;

    while( row < 23 )
    {
        for( column = 1; column < 23; column++ )
        {
            if( map[row][column] == 1 ) continue;
            up = map[row - 1][column];
            down = map[row + 1][column];
            left = map[row][column - 1];
            right = map[row][column + 1];
            if( ( up + down + left + right ) == 3 ) ends++;
        }
        row++;
    }
    return ends;
}