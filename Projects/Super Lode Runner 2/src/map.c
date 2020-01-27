#include "main.h"
#include <math.h>
#include <stdio.h>
//#include "GameObject.h"

//Height and width in number of tiles
#define MAPW  32 
#define MAPH  18 

#define TILEMAPW 16
#define TILEMAPH 17

//GameObject l[20] ={0};

int Map[] ={85, 85, 85, 85, 85, 3,BONUUSIMG, BONUUSIMG, 1, 0, 0, BONUUSIMG, BONUUSIMG, 85, 85, 85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 85, 85, 85, 85, 85,
 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85,
  85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85,
   85, 85, 85, 75, 75, 75, 75, 73, 85, 85, 85, 85, 85, 0, 0, 0, 0, 75, 75, 75, 75, 75, 75, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 
   85, 85, 0, 0, 0, 85, 73, 85, 85, 85, 85, 85, 73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 0,
    0, 0, 85, 73, 0, 0, 0, 0, 0, 73, 75, 75, 75, 75, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 0, 0, 0, 85, 
    85, 85, 85, 85, 85, 73, 73, 0, 0, 0, 0, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 85, 
    85, 85, 73, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 
    85, 73, 0, 0, 0, 0, 73, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85,
     85, 85, 85, 73, 85, 85, 85, 85, 85, 0, 0, 75, 75, 75, 73, 85, 85, 85, 85, 85, 85, 73, 75, 75, 75, 0, 73, 0, 0, 0, 0, 0, 0, 0,
      0, 73, 0, 0, 85, 85, 85, 85, 85, 85, 85, 0, 73, 85, 85, 85, 85, 85, 85, 73, 0, 0, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85,
       85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85, 73, 0, 0, 0, 0, 0, 0, 85, 85, 85, 73, 85, 85, 
       85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 73, 85, 85, 85, 85, 85, 85, 85, 73, 0, 0, 0, 0, 0, 0, 85, 85, 85, 73, 85, 85, 85, 85,
        85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 73, 85, 85, 85,
         85, 85, 85, 85, 85, 73, 85, 85, 85, 85, 85, 85, 85, 85, 85, 0, 0, 0, 0, 0, 0, 0, 73, 0, 0, 0, 0, 0, 73, 0, 0, 0, 0, 0, 0,
          0, 0, 73, 0, 0, 0, 0, 0, 0, 0, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 
          85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
           85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85};


int TableMap[MAPW][MAPH] = {0} ;

void InitMap(GameObject *l[])
{
    for (int y = 0; y < MAPH; y++)
    {
        for (int x = 0; x < MAPW; x++)
        {
            int tile = Map[ x + y * MAPW ] ;
            if (tile !=0 && tile!=1 && tile !=BONUUSIMG && tile!=3)
            {
                
                TableMap[x][y] = tile ;
            }
            else 
            {

                if(tile == 1)
                {
                   InitPlayers(l , Vector2 (x * TILEW , y * TILEH),1,tile);
                }
                if(tile ==3)
                {
                   InitPlayers(l , Vector2 (x * TILEW , y * TILEH),2,tile);
                }
                
                if(tile == BONUUSIMG)
                {
                    InitBonus(l , Vector2 (x * TILEW , y * TILEH),BONUUSIMG);
                }

                if(tile == 3/*Temp Enemy Test*/)
                {
                    InitEnemy(l,Vector2 (x * TILEW , y * TILEH));
                }
                TableMap[x][y] = -1  ;
            }
            
        }
    }
  //  DefineGameObjectTable(&l);
}

//Lets you know which tile is at a given position
int GetTile(Vector2 Pposition)
{
    int x = ceil ( Pposition.x / TILEMAPW ) ;  
    int y = ceil ( Pposition.y / TILEMAPH );

    return TableMap[x][y] ;

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