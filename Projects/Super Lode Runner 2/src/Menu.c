#include "main.h"
#include <raylib.h>

#define CURSOR 94
#define CCURSORH 112
#define CURSORW 120

Texture2D MenuTexture = {0};

struct Cursor
{
    Vector2 Position[2] ;
  
    int CurentPos ;
};

struct Cursor cursor ;
Vector2 cursorPos ;

void InitMenu()
{
    MenuTexture = LoadTexture("Assets/Image/Menu.png") ;

    cursor.Position[0] = Vector2(CURSORW,CCURSORH) ;//Player 1
    cursor.Position[1] = Vector2(CURSORW,CCURSORH + 17); //Player2
    cursor.Position[2] = Vector2(CURSORW,CCURSORH + 34); // Edit mode
    
    cursor.CurentPos = 0;
    cursorPos = cursor.Position[cursor.CurentPos] ;
    
}

void UpdateCursor(int *Scene)
{
     if (IsKeyPressed(KEY_W)||IsGamepadButtonReleased(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_UP)) //UP
     {
         if(cursor.CurentPos ==0)
         {
            cursor.CurentPos = 2;
            cursorPos= cursor.Position[cursor.CurentPos] ;
            return;
         }
        
        cursor.CurentPos -=1;
        cursorPos = cursor.Position[cursor.CurentPos] ;
        return ;

     } else  if (IsKeyPressed(KEY_S)||IsGamepadButtonReleased(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_DOWN)) //DOWN
     {
             if(cursor.CurentPos ==2)
         {
            cursor.CurentPos = 0;
            cursorPos= cursor.Position[cursor.CurentPos] ;
            return;
         }
        
        cursor.CurentPos +=1 ;
        cursorPos = cursor.Position[cursor.CurentPos] ;
        return ;
     }else if (IsKeyPressed(KEY_ENTER)||IsGamepadButtonReleased(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_MIDDLE_RIGHT)) //Validate
     {
        if(cursor.CurentPos ==0)
        {
            SelectedCountPlayer(1);
            InitMapExecute();
            LoadScene(GamePlay,Scene);
            return;
            
        }else if(cursor.CurentPos ==1)
        {
            SelectedCountPlayer(2);
            InitGamePlay();
            LoadScene(GamePlay,Scene);
            return; 
        }      
    }   
}

void DrawMenu(Texture2D tilset ,Rectangle ListeRectangle[])
{
    DrawTexturePro(MenuTexture,
    Rectangle(0,0,MenuTexture.width , MenuTexture.height),
    Rectangle(0,0,SCREENW,SCREENH),
    Vector2Zero,
    0,
    WHITE) ;

    //Draw Cursore
    Rectangle targetRect ;
    targetRect= Rectangle( ListeRectangle[CURSOR].x,
     ListeRectangle[CURSOR].y,
     ListeRectangle[CURSOR].width,
     ListeRectangle[CURSOR].height);

    DrawTexturePro(tilset,
        targetRect,
        Rectangle(cursorPos.x,cursorPos.y,TILEW/2,TILEH/2),
        Vector2Zero,
        0,
        WHITE) ;
}