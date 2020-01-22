#include "main.h"
#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <raymath.h>



//Declaration function
void InitAnimation() ;
void MouvPlayer(float SpeedX , float SpeedY);

bool CheckGround();


//POSITION PLAYER
struct GameObject Player ;
int Gravity = 10 ;


void InitPlayer()
{  
    InitAnimation();
    //Init position player
    Player.Position.x = 127 ;
    Player.Position.y = 0 ;
    //Init speed 
    Player.Speed = 8 ;
    Player.MaxSpeed = 50 ;
    Player.Velocity = Vector2Zero;
    Player.isGround = false;
    Player.isClimbing = false;
    Player.Offset = Vector2Zero ;
    Player.Animation.Pause = false ;

}


Vector2 InputManager()
{
    if (IsKeyDown(KEY_W)) //UP
    {
        MouvPlayer( 0 ,-Player.Speed ) ;
    } 
    else if (IsKeyDown(KEY_D))//RIGHT
    {
        Player.Flip = true ;
        MouvPlayer( Player.Speed , 0 ) ;
    }
    else if (IsKeyDown(KEY_A))//LEFT
    {
        Player.Flip = false ;
        MouvPlayer( -Player.Speed , 0 ) ;
    }
    else if (IsKeyDown(KEY_S))//DOWN
    {
        MouvPlayer(0 ,Player.Speed ) ;
    }
    else
    {
      MouvPlayer(0 ,0);
    
    }

    /*Stop Glimbing Stick*/
     if (IsKeyReleased(KEY_SPACE))
    {
        if(Player.isClimbingStick)
        {
            /*Stick Canxel*/
            ExitToStick(&Player);
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

void DrawInfoPlayer()
{
    DrawText(FormatText("isGlimbing: %d \nisLadder: %d \nVelocityY: %f \nVelocityX: %f \n" ,
     Player.isClimbing ,
     Player.isLadder,
     Player.Velocity.y,
     Player.Velocity.x),
     30,10,30,GREEN);
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

void MouvPlayer(float SpeedX , float SpeedY )
{
   
   if( CheckIsGlimbing(&SpeedX,&SpeedY,&Player))
   {
       return ;

   } 
   else if(!Player.isClimbing)
   {   //Check Is Player Touch Ground
       Player.isGround = CheckGround();
       if(Player.isGround)
       {
           Player.isGround = true ;
           //Fixe Velocity.X
            if(SpeedX == 0)
            {
                Player.Velocity.x = 0 ;
                AppliqueAnimation(ANIMATIONIDLE,2,&Player) ;
                return;
            }
 
        }
        else 
        {
           
           Player.Velocity.y += Gravity ;

            //Fixe Max Speed and Axe Y
           if(Player.Velocity.y > Player.MaxSpeed)
           {
               Player.Velocity.y = Player.MaxSpeed;
           }

           //Move Player and Axe Y
           Player.Position.y += Player.Velocity.y * 0.014 ;

           //Check if we are playing the right animation
            AppliqueAnimation(ANIMATIONFALL ,3 , &Player);

        } //End Gravity check
        
        //Fixe Max Speed and Axe X
         Player.Velocity.x += SpeedX  ;
        if(Player.Velocity.x > Player.MaxSpeed  )
        {
            Player.Velocity.x = Player.MaxSpeed ; 

        } else if(Player.Velocity.x < -Player.MaxSpeed  ) 
        {
            Player.Velocity.x = -Player.MaxSpeed ; 
        }

        //Save player position before moving 
        float oldx = Player.Position.x ;

        //Move Player and Axe X
        Player.Position.x += Player.Velocity.x * 0.014 ;

        //Check Collision new Possition
        if(CheckCollision(&Player,false))
        {
            Player.Velocity.x = 0 ;
            Player.Position.x = oldx ;
            return ;
        }

        //Check if we are playing the right animation
        if(Player.isGround )
        {
            AppliqueAnimation(ANIMATIONLEFT ,3 , &Player);
        }    
   }//End Check Glimbing
  
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

