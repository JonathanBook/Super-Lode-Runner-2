
#include <raylib.h>
#include "main.h"
#include <stdio.h>

#define SCREENH 240
#define SCREENW 256

Texture2D tilset ={0} ;

Rectangle ListeRectangle[97] ;

Scale CurentScale = Scale(0,0);


void ScaleUpdate ();
void TileDecoup();




int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 426;
    int screenHeight = 240;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Super Lode Runner");
    SetWindowMinSize(SCREENW,SCREENH);
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    tilset = LoadTexture("Assets/Image/Tilset Super Lode Runner2.png");
    TileDecoup();
    InitPlayer();
    InitMap();
    RenderTexture2D targetTexture = LoadRenderTexture (MAPRESOW , MAPRESOH ) ;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        ScaleUpdate() ;
        InputManager();
        //CameraManager();
        //----------------------------------------------------------------------------------
    
        // Draw
        //----------------------------------------------------------------------------------
        //Je DESSINE MA TEXTURE
        BeginTextureMode(targetTexture);

            ClearBackground(BLACK);
            DrawMap(tilset,ListeRectangle);
            DrawPlayer(tilset,ListeRectangle);
            DrawFPS(10,10);


        EndTextureMode();

        //JAFFICHE MA TEXTURE 
        BeginDrawing();
             ClearBackground(WHITE);
            
            DrawTexturePro(targetTexture.texture,
            Rectangle(0 ,-SCREENH,-SCREENW,SCREENH) ,
             Rectangle( (SCREENW*1.4) * CurentScale.l , 240  * CurentScale.h ,256 * CurentScale.l  , 240 * CurentScale.h  ),
             Vector2Zero ,
              180,
             WHITE);
          

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    

    // De-Initialization

    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;


}
void TileDecoup()
{
    //H=hauteur
    //L=Largeur

    int count = -1 ;
    for ( int H = 0; H <tilset.height/TILEH; H++)
    {
        for (int L = 0; L < tilset.width/TILEW; L++)
        {
            count +=1;
            ListeRectangle[count] = Rectangle( L * TILEW , H * TILEH , TILEW , TILEH ) ;
        }

    }
        
    
}

void ScaleUpdate ()
{
    int WinW = GetScreenWidth();
    int WinH = GetScreenHeight();

    if(CurentScale.l != WinW/426|| CurentScale.h != WinH/240 )
    {
      
        CurentScale.l = WinW/426 ;
        CurentScale.h = WinH/240;
            printf("L %f \n",CurentScale.l) ;
            printf("H %f \n",CurentScale.h) ;
    }
    if(CurentScale.l ==0 || CurentScale.h == 0 )
    {
        CurentScale.l =1 ;
        CurentScale.h =1 ;
    }
}

