#include "main.h"
#include <stdio.h>
#include <raymath.h>
#include "Sound.h"
#include <raylib.h>
//#include "GameObject.h"

//Declaration function
void InitAnimation() ;
int CountPlayer = 0;
int InitCount =0 ;
//POSITION PlayerOne
struct GameObject PlayerOne ;
struct GameObject PlayerTwo ;

//Var BLoc Destroy & Build
struct Bloc
{
    Vector2 BlocPos;
    float TimeBloc;
    int CurentImg ;
    bool isActive;

    bool isBuild;
    float TimeToRebuild;
};
struct Bloc blocListe[10] ={0};
int ContBlocListe =0 ;
int AnimationBloc[5]={0};

void Init(GameObject *Acteur,GameObject *liste[],Vector2 Spawn);
void InputPlayerOne();
void InputPlayerTwo();
void InitAnimationPlayerOne();
void InitAnimationPlayerTwo();
void UpdateBloc();
void DestroyBloc(Vector2 PosB );
void InitAnimationBloc();

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
        InitAnimationBloc();
        return;
    }
    else if(CountPlayer ==2)
    {
        if(player == 1)
        {
            InitAnimationPlayerOne();
            Init(&PlayerOne,liste , Spawn);
            InitAnimationBloc();
        }else
        {
        
            InitAnimationPlayerTwo();
            Init(&PlayerTwo,liste , Spawn);
        }  
    }
//Update Animation Bloc Destroy Re Build
    UpdateBloc();
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
  UpdateBloc();
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

void InitAnimationBloc()
{
    AnimationBloc[0] =94 ;
    AnimationBloc[1] =93 ;
    AnimationBloc[2] =92 ;
    AnimationBloc[3] =91 ;
    printf("ANIMATION BLOC DESTROY CHARGER \n") ;
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
      if (IsKeyDown(KEY_W) ||IsGamepadButtonDown(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_UP)) //UP
    {
        MouvActeur( 0 ,-PlayerOne.Speed ,&PlayerOne ) ;
    } 
    else if (IsKeyDown(KEY_D)||IsGamepadButtonDown(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_RIGHT))//RIGHT
    {
        PlayerOne.Flip = true ;
        MouvActeur( PlayerOne.Speed , 0 ,&PlayerOne ) ;
    }
    else if (IsKeyDown(KEY_A)||IsGamepadButtonDown(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_LEFT))//LEFT
    {
        PlayerOne.Flip = false ;
        MouvActeur( -PlayerOne.Speed , 0 ,&PlayerOne ) ;
    }
    else if (IsKeyDown(KEY_S)||IsGamepadButtonDown(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_DOWN))//DOWN
    {
        MouvActeur(0 ,PlayerOne.Speed ,&PlayerOne ) ;
    }
    else
    {
      MouvActeur(0 ,0 ,&PlayerOne);
    
    }
    if(IsKeyReleased(KEY_Q)||IsGamepadButtonReleased(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    {
        DestroyBloc(Vector2Add(PlayerOne.Position , Vector2(-24,8)));

    }else if(IsKeyReleased(KEY_E)||IsGamepadButtonReleased(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
    {
        DestroyBloc(Vector2Add(PlayerOne.Position , Vector2(16,8)));
    }
    
   
    UpdateAnimation(&PlayerOne);
}

void InputPlayerTwo()
{
      if (IsKeyDown(KEY_UP)||IsGamepadButtonDown(GAMEPAD_PLAYER2 , GAMEPAD_BUTTON_LEFT_FACE_UP)) //UP
    {
        MouvActeur( 0 ,-PlayerTwo.Speed ,&PlayerTwo ) ;
    } 
    else if (IsKeyDown(KEY_RIGHT)||IsGamepadButtonDown(GAMEPAD_PLAYER2 , GAMEPAD_BUTTON_LEFT_FACE_RIGHT))//RIGHT
    {
        PlayerTwo.Flip = true ;
        MouvActeur( PlayerTwo.Speed , 0 ,&PlayerTwo ) ;
    }
    else if (IsKeyDown(KEY_LEFT)||IsGamepadButtonDown(GAMEPAD_PLAYER2 , GAMEPAD_BUTTON_LEFT_FACE_LEFT))//LEFT
    {
        PlayerTwo.Flip = false ;
        MouvActeur( -PlayerTwo.Speed , 0 ,&PlayerTwo ) ;
    }
    else if (IsKeyDown(KEY_DOWN)||IsGamepadButtonDown(GAMEPAD_PLAYER2 , GAMEPAD_BUTTON_LEFT_FACE_DOWN))//DOWN
    {
        MouvActeur(0 ,PlayerTwo.Speed ,&PlayerTwo ) ;
    }
    else
    {
      MouvActeur(0 ,0 ,&PlayerTwo);
    
    }

    if(IsKeyReleased(KEY_Q)||IsGamepadButtonReleased(GAMEPAD_PLAYER2 , GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    {
        DestroyBloc(Vector2Add(PlayerOne.Position , Vector2(-24,8)));

    }else if(IsKeyReleased(KEY_E)||IsGamepadButtonReleased(GAMEPAD_PLAYER2 , GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
    {
        DestroyBloc(Vector2Add(PlayerOne.Position , Vector2(16,8)));
    }

    UpdateAnimation(&PlayerTwo);
}

void DestroyBloc(Vector2 PosB )
{
    int Tile = GetTile(PosB);
    if( Tile!= LADER && Tile != STICK && Tile!=-1 )
    {
        for (int i = 0; i < 10; i++)
        {
            if(!blocListe[i].isActive)
            {
                PlayFx(0);
                struct Bloc B ;
                B.BlocPos = PosB ;
                B.TimeBloc = 0 ;
                B.TimeToRebuild =0;
                B.CurentImg = 0 ;
                B.isActive = true ;
                B.isBuild = false;

                blocListe[i] = B;
                return;

            }
        }
    }
   
}

void UpdateBloc()
{
   int curentImgP;
    for (int i = 0; i < 10 ; i++)
    {
        if(blocListe[i].isActive)
        {
            
            //Re Build BLOC

            if(blocListe[i].isBuild == true)
            {
                
                if(blocListe[i].TimeToRebuild >=10 )
                {
                    
                    if(blocListe[i].TimeBloc >=1)
                    {
                        blocListe[i].TimeBloc = 0;
                        blocListe[i].CurentImg -=1;
                        if(blocListe[i].CurentImg <0)
                        {
                            curentImgP = WALL;
                            blocListe[i].isActive = false ;
                            SetTile(blocListe[i].BlocPos ,curentImgP);
                        }
                        else
                        {
                            curentImgP = AnimationBloc[blocListe[i].CurentImg] ;
                            SetTile(blocListe[i].BlocPos ,curentImgP);
                        }
                    }else
                    {
                        blocListe[i].TimeBloc +=0.15f;
                    }
                    
                    
                }else
                {
                    blocListe[i].TimeToRebuild +=0.015f; 
                }
                
            }
            //Destroy BLoc    
            else if(blocListe[i].isBuild == false)
            {
               
                if(blocListe[i].TimeBloc >=1)
                {
                    curentImgP =AnimationBloc[ blocListe[i].CurentImg] ;

                    blocListe[i].TimeBloc =0 ;

                    blocListe[i].CurentImg +=1;

                    //Check No Max Img
                    if(blocListe[i].CurentImg >3)
                    {
                        blocListe[i].CurentImg =3;
                        curentImgP =-1;
                        blocListe[i].isBuild = true;
                        blocListe[i].TimeToRebuild = 0;
                        blocListe[i].TimeBloc =0;
                        SetTile(blocListe[i].BlocPos ,curentImgP);
                    }else
                    {
                        curentImgP = AnimationBloc[blocListe[i].CurentImg] ;
                        SetTile(blocListe[i].BlocPos ,curentImgP);
                    }
                }else
                {
                    blocListe[i].TimeBloc +=0.05f;
                }
                
                
                
                
            }
            
            
        
        }
       
    }
    
}
