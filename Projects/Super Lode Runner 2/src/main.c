
#include <raylib.h>
#include "main.h"
#include <stdio.h>
#include <raymath.h>


Texture2D tilset ={0} ;

Rectangle ListeRectangle[97] ;

Scale CurentScale = Scale(0,0);


void ScaleUpdate ();
void TileDecoup();
void DrawMenu(Texture2D tilset ,Rectangle ListeRectangle[]);
void InitMenu();
void UpdateCursor(SceneManager *Scene);
void CameraLimiteScheck(Camera2D *camera);
void DrawInfoPlayer();
SceneManager Scene ;




int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 426;
    int screenHeight = 240;

 

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Super Lode Runner");
    SetWindowMinSize(SCREENW,SCREENH);
    
    //CAMERA 2D
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ SCREENW/2, SCREENH/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    tilset = LoadTexture("Assets/Image/Tilset Super Lode Runner2.png");
    TileDecoup();
    InitPlayer();
    InitMap();
    InitMenu();
    Scene.CurentScene = 0 ;
    RenderTexture2D targetTexture = LoadRenderTexture (SCREENW , SCREENH ) ;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        ScaleUpdate() ;
        if(Scene.CurentScene == GamePlay)
        {
            
            camera.target =Vector2(InputManager().x + 20 , InputManager().y + 20 );
           CameraLimiteScheck(&camera);
            
        }else if(Scene.CurentScene == Menu)
        {
            camera.target = Vector2(SCREENW/2,SCREENH/2);
            UpdateCursor(&Scene);
        }
        
        
        //CameraManager();
        //----------------------------------------------------------------------------------
    
        // Draw
        //----------------------------------------------------------------------------------
        //Je DESSINE MA TEXTURE
        BeginTextureMode(targetTexture);
            BeginMode2D(camera);
                
                ClearBackground(BLACK);

                if(Scene.CurentScene ==GamePlay)
                {
                    DrawMap(tilset,ListeRectangle);
                    DrawPlayer(tilset,ListeRectangle);

                }else if(Scene.CurentScene == Menu)
                {
                    DrawMenu(tilset ,ListeRectangle);
                }
                
            EndMode2D();

        EndTextureMode();

        //JAFFICHE MA TEXTURE 
        BeginDrawing();
             ClearBackground(WHITE);
            
            DrawTexturePro(targetTexture.texture,
                Rectangle(0 ,0,-SCREENW,SCREENH) ,
                Rectangle( SCREENW*1.4 * CurentScale.l ,
                SCREENH * CurentScale.h ,
                SCREENW * CurentScale.l  , 
                SCREENH* CurentScale.h  ),
                Vector2Zero ,
                180,
                WHITE
            );
            DrawFPS(10,10);
            DrawInfoPlayer();
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
    
    }
    if(CurentScale.l ==0 || CurentScale.h == 0 )
    {
        CurentScale.l =1 ;
        CurentScale.h =1 ;
    }
}

void CameraLimiteScheck(Camera2D *camera)
{
    //Camera Limit Manager
    if(camera->target.x <145)
    {
        camera->target.x = 145;
    }
    if(camera->target.x >380)
    {
        camera->target.x = 380;
    }
    if(camera->target.y <107)
    {
        camera->target.y = 107; 
    }
        
    if(camera->target.y >180)
    {
        camera->target.y = 180 ; 
    }
                    
}