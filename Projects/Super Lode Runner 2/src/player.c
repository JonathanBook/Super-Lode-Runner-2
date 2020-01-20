#include "main.h"
#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <raymath.h>



//Declaration function
void InitAnimation() ;
void MouvPlayer(int NumeroAnimation  , float SpeedX , float SpeedY ,int MaxFrame);

bool CheckGround();


//POSITION PLAYER
struct GameObject Player ;
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
    Player.Offset = Vector2Zero ;
    Player.Animation.Pause = false ;
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
    else if (IsKeyDown(KEY_SPACE))//LEFT
    {
        if(Player.isClimbingStick)
            ExitToStick(&Player);
    }
    else 
    {
       MouvPlayer(AnNul , 0 ,0 ,1);
        if(Player.isGround)
        {
            AppliqueAnimation(ANIMATIONIDLE,2,&Player);
            Player.Velocity = Vector2Zero ;
        }
  
    }
    
    UpdateAnimation(&Player);

    return Player.Position ;
}






void DrawPlayer(Texture2D tilset ,Rectangle ListeRectangle[])
{
    int i = Player.Animation.Frame[Player.Animation.NumeroAnimation][Player.Animation.CurentFrame] ;

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


    Vector2 tp = Vector2(Player.Position.x +16 , Player.Position.y +16 );
    tp = Vector2Add (tp , Player.Offset) ;
    DrawCircle(tp.x,tp.y,1,GREEN);
}


void InitAnimation()
{
    //Idle Position
   Player.Animation.Frame[0][0] = 0;
   Player.Animation.Frame[0][1] = 1;
    printf("ANIMATION IDLE CHARGER \n") ;
   //Walk Left Right
    Player.Animation.Frame[1][0] = 14 ;
    Player.Animation.Frame[1][1] = 13;
    Player.Animation.Frame[1][2] = 12;
    printf("ANIMATION LEFT AND RIGHT CHARGER \n") ;
    //Climbing LADER
    Player.Animation.Frame[2][0] = 24 ;
    Player.Animation.Frame[2][1] = 25;

    printf("ANIMATION GLIMP CHARGER \n") ;
    //And Climbing
    Player.Animation.Frame[3][0] = 38 ;
    Player.Animation.Frame[3][1] = 37 ;
    Player.Animation.Frame[3][2] = 36 ;
     printf("ANIMATION GLIMP AND CHARGER \n") ;
    //Climbing Stick
    Player.Animation.Frame[4][0] = 51 ;
    Player.Animation.Frame[4][1] = 52 ;
    Player.Animation.Frame[4][2] = 53 ;
    Player.Animation.Frame[4][2] = 54 ;
     printf("ANIMATION HUP CHARGER \n") ;
    //Fall Climbing Stick
    Player.Animation.Frame[5][0] = 49 ;
    Player.Animation.Frame[5][1] = 50 ;
    printf("ANIMATION CHUTE STICK CHARGER \n") ;
    //Fall
    Player.Animation.Frame[6][0] = 60 ;
    Player.Animation.Frame[6][1] = 61 ;
    Player.Animation.Frame[6][2] = 62 ;
    printf("ANIMATION CHUTE CHARGER \n") ;
}

void MouvPlayer(int NumeroAnimation  , float SpeedX , float SpeedY ,int MaxFrame )
{
    if( SpeedY >0 && GetTile( Vector2Add( Player.Position , Vector2(-8,TILEH))) == LADER || 
        SpeedY <0 && GetTile( Vector2Add( Player.Position , Vector2(-8,-1)))==LADER ||
        Player.isClimbing && Player.isLadder )
    {   
        Player.Velocity = Vector2Zero;
        AppliqueAnimation(ANIMATIONGLIMBINGLADER,2,&Player);
        ClimbingLadder(  &SpeedX ,  &SpeedY ,  &Player) ;
        return ;
    } 
    else
    {
       if( SpeedX >0 && GetTile( Vector2Add( Player.Position , Vector2(1,0))) == STICK || 
        SpeedX <0 && GetTile( Vector2Add( Player.Position , Vector2(-16,0)))==STICK ||
        Player.isClimbing && Player.isClimbingStick)
        {
        
            ClimbingStick(  &SpeedX ,  &SpeedY ,  &Player) ;
            return ;
        } 
        else
        {
               //If the player does not move and he touches the ground we quit the function
            if(SpeedX == 0 && Player.isGround ==true || Player.isClimbing )
            {
                Player.Velocity.x =0 ;
                return;
            }
            
        }
        
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

    if(CheckCollision(&Player,false))
        Player.Position.x = oldx ;
   
    //We check her to apply gravity or not
    if(Player.isClimbing == false && !Player.isGround )
        Player.Velocity.y += Gravity ;
        Player.Position.y += Player.Velocity.y * 0.014 ;
        if(Player.Velocity.y > Player.MaxSpeed)
            Player.Velocity.y = Player.MaxSpeed;

    //Check if we are playing the right animation
   AppliqueAnimation(NumeroAnimation ,MaxFrame , &Player);
}



 //Check if the hero hits the ground or not
bool CheckGround()
{
    if( CheckCollision(&Player,true))
    {
        float pos = ceil( (Player.Position.y-10)/TILEH ) * TILEH ;
        Player.Position.y = pos  ;
        Player.Velocity.y =0 ;
        return true;
    }
  
    return false ;
    
}

