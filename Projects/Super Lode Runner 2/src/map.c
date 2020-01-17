#include "main.h"
#include <math.h>
#include <stdio.h>

//Height and width in number of tiles
#define MAPW  32 
#define MAPH  18 

#define TILEMAPW 16
#define TILEMAPH 17

//Definition of the different tiles
#define WALL 85
#define LADER 75
#define STICK 73

int Map[] ={85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 0, 85, 85, 85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 85, 85, 85, 85, 85,
 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85,
 85, 85, 85, 0, 0, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85,
 0, 73, 75, 75, 75, 75, 73, 85, 85, 85, 85, 85, 0, 75, 75, 75, 75, 75, 75, 75, 75, 75, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85,
 0, 73, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73,
 85, 85, 85, 85, 73, 0, 0, 0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 85,
 85, 85, 85, 85, 85, 73, 0, 0, 0, 0, 0, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 0, 85,
 85, 85, 73, 75, 75, 75, 75, 0, 85, 85, 85, 85, 85, 85, 85, 85, 0, 0, 0, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85,
 85, 0, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85, 0, 75, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85,
 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 0, 73, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 73, 
 0, 0, 85, 85, 85, 85, 85, 85, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85,
 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85,
 0, 0, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 
 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85,
 85, 85, 85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 85, 85, 85, 85,
 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85};



int TableMap[MAPW][MAPH] = {0} ;

void InitMap()
{
    for (int y = 0; y < MAPH; y++)
    {
        for (int x = 0; x < MAPW; x++)
        {
            int tile = Map[ x + y * MAPW ] ;
            if (tile !=0)
            {
                /* code */
                TableMap[x][y] = tile ;
            }
            else
            {
                /* code */
                TableMap[x][y] = -1  ;
            }
        }
    }
    
}

//Lets you know which tile is at a given position
int GetTile(Vector2 Pposition)
{
    int x = ceil ( Pposition.x / TILEMAPW ) ;  
    int y = ceil ( Pposition.y / TILEMAPH );

    if( TableMap[x][y]!=NULL)
        return TableMap[x][y] ;

    printf("VALUE NULL CHECK POSITION HEREURE \n ") ;  

}

//Allows you to modify a tile at a given position
bool SetTile(Vector2 Pposition , int Ptile)
{
    if(GetTile(Pposition)!=NULL)
    {
        int x = ceil ( Pposition.x / TILEMAPW ) ;  
        int y = ceil ( Pposition.y / TILEMAPH );

        TableMap[x][y] = Ptile ;
        return true ;
    }

    printf("HEREUR TILE NOT SET POSITION INVALIDE \n ") ;
    return false ;

}

//Draw the map on the screen
void DrawMap(Texture2D tilset, Rectangle ListeRectangle[])
{
  

    for (int y =  0; y < MAPH; y++)
    {
        for (int x =  0; x < MAPW; x++)
        {

            int tile = TableMap[x][y];
            if (tile !=NULL && tile !=-1)
            {
                /* code */
                  DrawTexturePro(tilset ,
                   ListeRectangle[tile-1 ],
                   Rectangle(x * TILEW , y * TILEH , TILEW , TILEH ),
                   Vector2Zero,0,WHITE);

            }
        }
    }
}