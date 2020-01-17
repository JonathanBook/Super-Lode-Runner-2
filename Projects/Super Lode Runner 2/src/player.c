#include "main.h"
#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <raymath.h>

//Define the dimensions of a tile
#define PLAYERTILEW 16
#define PLAYERTILEH 17

//Definition of animation
#define ANIMATIONIDLE 0
#define ANIMATIONLEFT 1
#define ANIMATIONRIGHT 1
#define ANIMATIONGLIMBINGLADER 2
#define ANIMATIONGLIMBINGSTICK 4
#define ANIMATIONFALLSTICK 5
#define ANIMATIONFALL 6

void InitAnimation() ;
void MouvPlayer(int NumeroAnimation  , float SpeedX , float SpeedY ,int MaxFrame);
void CheckAnimation(int NumeroAnimation , int MaxFrame);
bool CheckGround();
bool CheckCollision(bool IsCheckGround);

//POSITION PLAYER
struct GameObject Player ;
float TimeAnimation = 0 ;
int Gravity = 10 ;


void InitPlayer()
{  
    
    InitAnimation();
    
    //Init position player
    Player.Position.x = 95 ;
    Player.Position.y = 164 ;
    //Init speed 
    Player.Speed = 8 ;
    Player.MaxSpeed = 50 ;
    Player.Velocity = Vector2(0,0);
    Player.isGround = false;
    Player.isClimbing = false;
}


Vector2 InputManager()
{
    float dt = 0.14;
    if (IsKeyDown(KEY_W)) //UP
    {
        MouvPlayer( ANIMATIONGLIMBINGLADER , 0 ,-Player.Speed , 2  ) ;
    } 
    else if (IsKeyDown(KEY_A))//LEFT
    {
        Player.Flip = false ;
        MouvPlayer( ANIMATIONLEFT , -Player.Speed  , 0 , 3  ) ;
    }
    else if (IsKeyDown(KEY_S))//DOWN
    {
        MouvPlayer( ANIMATIONGLIMBINGLADER , 0 ,Player.Speed , 3  ) ;
    }
    else if (IsKeyDown(KEY_D))//RIGHT
    {
        Player.Flip = true ;
        MouvPlayer( ANIMATIONRIGHT , Player.Speed  , 0 , 3  ) ;
    }
    else
    {
        MouvPlayer(ANIMATIONIDLE , 0 , 0 ,2 ) ;
    }
    
    UpdateAnimation(dt);

    return Player.Position ;
}



void UpdateAnimation(dt)

{ 
  
  //Update Tumer
  TimeAnimation +=0.05 ;

  if(TimeAnimation >=1)
  {
      TimeAnimation = 0 ;
      Player.CurentFrame ++ ;
  }

  if(Player.CurentFrame >= Player.MaxFrame)
        Player.CurentFrame = 0 ;
    
}


void DrawPlayer(Texture2D tilset ,Rectangle ListeRectangle[])
{
    int i = Player.Frame[Player.NumeroAnimation][Player.CurentFrame] ;

    Rectangle targetRect =  ListeRectangle[i];
    
    //Flip management
    if(Player.Flip)
        targetRect = Rectangle( ListeRectangle[i].x, ListeRectangle[i].y,- ListeRectangle[i].width, ListeRectangle[i].height);

    
    DrawTexturePro (tilset ,
        targetRect ,
        Rectangle( Player.Position.x , Player.Position.y ,PLAYERTILEW , PLAYERTILEH ),
        Vector2Zero,
        0 ,
        WHITE ) ;
  
}


void InitAnimation()
{
    //Idle Position
   Player.Frame[0][0] = 0;
   Player.Frame[0][1] = 1;
    printf("ANIMATION IDLE CHARGER \n") ;
   //Walk Left Right
    Player.Frame[1][0] = 14 ;
    Player.Frame[1][1] = 13;
    Player.Frame[1][2] = 12;
    printf("ANIMATION LEFT AND RIGHT CHARGER \n") ;
    //Climbing LADER
    Player.Frame[2][0] = 24 ;
    Player.Frame[2][1] = 25;

    printf("ANIMATION GLIMP CHARGER \n") ;
    //And Climbing
    Player.Frame[3][0] = 38 ;
    Player.Frame[3][1] = 37 ;
    Player.Frame[3][2] = 36 ;
     printf("ANIMATION GLIMP AND CHARGER \n") ;
    //Climbing Stick
    Player.Frame[4][0] = 51 ;
    Player.Frame[4][1] = 52 ;
    Player.Frame[4][2] = 53 ;
    Player.Frame[4][2] = 54 ;
     printf("ANIMATION HUP CHARGER \n") ;
    //Fall Climbing Stick
    Player.Frame[5][0] = 49 ;
    Player.Frame[5][1] = 50 ;
    printf("ANIMATION CHUTE STICK CHARGER \n") ;
    //Fall
    Player.Frame[6][0] = 61 ;
    Player.Frame[6][1] = 62 ;
    Player.Frame[6][2] = 63 ;
    printf("ANIMATION CHUTE CHARGER \n") ;
}

void MouvPlayer(int NumeroAnimation  , float SpeedX , float SpeedY ,int MaxFrame )
{
    
    //If the player does not move and he touches the ground we quit the function
    if(SpeedX == 0 && Player.isGround ==true )
    {
        Player.Velocity.x =0 ;
        return;
    }

    //Save player position before moving 
    float oldx = Player.Position.x ;
    float oldy = Player.Position.y ;
    
    //Check if the hero hits the ground or not
     Player.isGround  = CheckGround();

    //Increases velocity and prevents it from exceeding the maximum speed
    //If the hero goes right
    if(SpeedX >=0 && Player.Velocity.x < Player.MaxSpeed)
    {
        Player.Velocity.x += SpeedX  ;
        
        if(Player.Velocity.x > Player.MaxSpeed  ) 
            Player.Velocity.x = Player.MaxSpeed ; 

    } 
    else
    {  
         //If the hero goes to the Left
        if(SpeedX <=0 && Player.Velocity.x > -Player.MaxSpeed)
        {
            Player.Velocity.x += SpeedX  ;
        
            if(Player.Velocity.x < -Player.MaxSpeed  ) 
                Player.Velocity.x = -Player.MaxSpeed ; 

        }
      
    }  
   
    //Hero  position.x velocity increment
    Player.Position.x += Player.Velocity.x * 0.014 ;
   
    //We check her to apply gravity or not
    if(Player.isClimbing == false && !Player.isGround )
        Player.Position.y += Gravity * 0.014 ;

    //Check if we are playing the right animation
   CheckAnimation(NumeroAnimation ,MaxFrame);
}


//Check if we are playing the right animation
void CheckAnimation(int NumeroAnimation , int MaxFrame)
{
    if(Player.NumeroAnimation != NumeroAnimation)
        Player.NumeroAnimation = NumeroAnimation ;
        Player.MaxFrame = MaxFrame ;
}
 //Check if the hero hits the ground or not
bool CheckGround()
{
    if( CheckCollision(true))
    {
        float pos = floor( Player.Position.y/TILEH ) * TILEH ;
        Player.Position.y = pos  ;
        return true;
    }

    return false ;
    
}

//Check the different collisions the hero may encounter
bool CheckCollision(bool IsCheckGround)
{
    Vector2 Offset = Vector2Zero ;

    if(Player.Velocity.x <0 && !IsCheckGround)
        Offset = Vector2(-TILEW,0); 
    
    int tile = GetTile( Vector2Add(Player.Position ,Offset) ) ;

   if ( tile != 0 && tile!=-1 )
        return true ;
    return false    ;
}