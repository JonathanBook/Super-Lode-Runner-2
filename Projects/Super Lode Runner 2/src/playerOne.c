#include "main.h"
#include <stdio.h>
#include <raymath.h>
#include "Sound.h"
#include <raylib.h>


//Declaration function
void InitAnimation() ;
int CountPlayer = 0;
int InitCount =0 ;
//POSITION PlayerOne
struct GameObject PlayerOne ;
struct GameObject PlayerTwo ;

void Init(GameObject *Acteur,GameObject *liste[],Vector2 Spawn);
void InputPlayerOne();
void InputPlayerTwo();
void InitAnimationPlayerOne();
void InitAnimationPlayerTwo();

void SelectedCountPlayer(int Count)
{
    CountPlayer = Count ;
}

void InitPlayers(GameObject *liste[],Vector2 Spawn,int player , int Tile)
{  
    if(CountPlayer ==1 && player == 1)
    {
        InitAnimationPlayerOne();
        Init(&PlayerOne,liste , Spawn);
        return;
    }
    else if(CountPlayer ==2)
    {
        if(player == 1)
        {
            InitAnimationPlayerOne();
            Init(&PlayerOne,liste , Spawn);
        }else
        {
        
            InitAnimationPlayerTwo();
            Init(&PlayerTwo,liste , Spawn);
        }  
    }
}


Vector2 InputManager()
{
  if(CountPlayer == 1)
  {
      InputPlayerOne();
  }
  else if(CountPlayer ==2)
  {
      InputPlayerOne();
      InputPlayerTwo();
  }
  
    return PlayerOne.Position ;
}


void InitAnimationPlayerOne()
{
    //Idle Position
   PlayerOne.Animation.Frame[0][0] = 0;
   PlayerOne.Animation.Frame[0][1] = 1;
    printf("ANIMATION IDLE CHARGER \n") ;
   //Walk Left Right
    PlayerOne.Animation.Frame[1][0] = 14 ;
    PlayerOne.Animation.Frame[1][1] = 13;
    PlayerOne.Animation.Frame[1][2] = 12;
    printf("ANIMATION LEFT AND RIGHT CHARGER \n") ;
    //Climbing LADER
    PlayerOne.Animation.Frame[2][0] = 24 ;
    PlayerOne.Animation.Frame[2][1] = 25;

    printf("ANIMATION GLIMP CHARGER \n") ;
    //And Climbing
    PlayerOne.Animation.Frame[3][0] = 38 ;
    PlayerOne.Animation.Frame[3][1] = 37 ;
    PlayerOne.Animation.Frame[3][2] = 36 ;
     printf("ANIMATION GLIMP AND CHARGER \n") ;
    //Climbing Stick
    PlayerOne.Animation.Frame[4][0] = 51 ;
    PlayerOne.Animation.Frame[4][1] = 52 ;
    PlayerOne.Animation.Frame[4][2] = 53 ;
    PlayerOne.Animation.Frame[4][2] = 54 ;
     printf("ANIMATION HUP CHARGER \n") ;
    //Fall Climbing Stick
    PlayerOne.Animation.Frame[5][0] = 49 ;
    PlayerOne.Animation.Frame[5][1] = 50 ;
    printf("ANIMATION CHUTE STICK CHARGER \n") ;
    //Fall
    PlayerOne.Animation.Frame[6][0] = 60 ;
    PlayerOne.Animation.Frame[6][1] = 61 ;
    PlayerOne.Animation.Frame[6][2] = 62 ;
    printf("ANIMATION CHUTE CHARGER \n") ;
}

void InitAnimationPlayerTwo()
{
    //Idle Position
   PlayerTwo.Animation.Frame[0][0] = 3;
   PlayerTwo.Animation.Frame[0][1] = 2;
    printf("ANIMATION IDLE CHARGER \n") ;
   //Walk Left Right
    PlayerTwo.Animation.Frame[1][0] = 17 ;
    PlayerTwo.Animation.Frame[1][1] = 16;
    PlayerTwo.Animation.Frame[1][2] = 15;
    printf("ANIMATION LEFT AND RIGHT CHARGER \n") ;
    //Climbing LADER
    PlayerTwo.Animation.Frame[2][0] = 26 ;
    PlayerTwo.Animation.Frame[2][1] = 27;

    printf("ANIMATION GLIMP CHARGER \n") ;
    //And Climbing
    PlayerTwo.Animation.Frame[3][0] = 41 ;
    PlayerTwo.Animation.Frame[3][1] = 40 ;
    PlayerTwo.Animation.Frame[3][2] = 39 ;
     printf("ANIMATION GLIMP AND CHARGER \n") ;
    //Climbing Stick
    PlayerTwo.Animation.Frame[4][0] = 58 ;
    PlayerTwo.Animation.Frame[4][1] = 57 ;
    PlayerTwo.Animation.Frame[4][2] = 56 ;
    PlayerTwo.Animation.Frame[4][2] = 55 ;
     printf("ANIMATION HUP CHARGER \n") ;
    //Fall Climbing Stick
    PlayerTwo.Animation.Frame[5][0] = 52 ;
    PlayerTwo.Animation.Frame[5][1] = 51 ;
    printf("ANIMATION CHUTE STICK CHARGER \n") ;
    //Fall
    PlayerTwo.Animation.Frame[6][0] = 65 ;
    PlayerTwo.Animation.Frame[6][1] = 64 ;
    PlayerTwo.Animation.Frame[6][2] = 63 ;
    printf("ANIMATION CHUTE CHARGER \n") ;
}



void Init(GameObject *Acteur,GameObject *liste[],Vector2 Spawn)
{
    //Init position PlayerOne
    Acteur->isActive = true ;
    Acteur->Position = Spawn;
    //Init speed 
    Acteur->Speed = 8 ;
    Acteur->MaxSpeed = 40 ;
    Acteur->Velocity = Vector2Zero;
    Acteur->isGround = false;
    Acteur->isClimbing = false;
    Acteur->Offset = Vector2Zero ;
    Acteur->Animation.Pause = false ;
    Acteur->Points = 0 ;
    liste[InitCount] = Acteur ;
    InitCount +=1;
}

void InputPlayerOne()
{
      if (IsKeyDown(KEY_W)) //UP
    {
        MouvPlayer( 0 ,-PlayerOne.Speed ,&PlayerOne ) ;
    } 
    else if (IsKeyDown(KEY_D))//RIGHT
    {
        PlayerOne.Flip = true ;
        MouvPlayer( PlayerOne.Speed , 0 ,&PlayerOne ) ;
    }
    else if (IsKeyDown(KEY_A))//LEFT
    {
        PlayerOne.Flip = false ;
        MouvPlayer( -PlayerOne.Speed , 0 ,&PlayerOne ) ;
    }
    else if (IsKeyDown(KEY_S))//DOWN
    {
        MouvPlayer(0 ,PlayerOne.Speed ,&PlayerOne ) ;
    }
    else
    {
      MouvPlayer(0 ,0 ,&PlayerOne);
    
    }

   
    UpdateAnimation(&PlayerOne);
}

void InputPlayerTwo()
{
      if (IsKeyDown(KEY_UP)) //UP
    {
        MouvPlayer( 0 ,-PlayerTwo.Speed ,&PlayerTwo ) ;
    } 
    else if (IsKeyDown(KEY_RIGHT))//RIGHT
    {
        PlayerTwo.Flip = true ;
        MouvPlayer( PlayerTwo.Speed , 0 ,&PlayerTwo ) ;
    }
    else if (IsKeyDown(KEY_LEFT))//LEFT
    {
        PlayerTwo.Flip = false ;
        MouvPlayer( -PlayerTwo.Speed , 0 ,&PlayerTwo ) ;
    }
    else if (IsKeyDown(KEY_DOWN))//DOWN
    {
        MouvPlayer(0 ,PlayerTwo.Speed ,&PlayerTwo ) ;
    }
    else
    {
      MouvPlayer(0 ,0 ,&PlayerTwo);
    
    }


    UpdateAnimation(&PlayerTwo);
}