#include "main.h"
#include <raylib.h>
#include <math.h>
#include <raymath.h>
#include <stdio.h>

void InitGlimbing(float *SpeedX , float *SpeedY , struct GameObject *Acteur,int Tile);
void MoveToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur);
void UpToExitLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur);
void DownExitToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur,int Tile);
void LeftAndRightExitToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur);
void VeloCityUpdate(float *SpeedX , float *SpeedY , struct GameObject *Acteur);




bool CheckIsGlimbing(float *SpeedX , float *SpeedY , GameObject *Acteur)
{
    /*Default Offset*/
    Acteur->Offset = Vector2(-TILEW/2 , -TILEH/2) ;

    int Tile =GetTile( Vector2Add( Acteur->Position , Acteur->Offset)); ;

    /*Define Offset*/
    if(*SpeedX >0 )
    {
        Acteur->Offset = Vector2(1,-TILEH/2) ;
        
    }else if ( *SpeedX < 0 )
    {
        Acteur->Offset = Vector2(-TILEW,-TILEH/2) ;
        
    }
     if(*SpeedY > 0)
    {
        Acteur->Offset = Vector2(-TILEW/2,1) ;
        
    }else if(*SpeedY <0)
    {
        Acteur->Offset = Vector2(-TILEW/2,-TILEH/2) ;
        
    }
    
    Tile = GetTile( Vector2Add( Acteur->Position , Acteur->Offset));
    
   if (Tile == LADER && *SpeedY!=0 || Tile == STICK || Acteur->isClimbing)
    {
        
        Glimbing(  SpeedX ,  SpeedY ,  Acteur,Tile) ;

        return true ;

    }
   return false ;
}


//Managed the ascent and descent to the ladder
void Glimbing(float *SpeedX , float *SpeedY,struct GameObject  *Acteur ,int Tile)
{   
    int tile = Tile ;
    float TOldY = Acteur->Position.y ;
    //If the day is not on the Ladder
    if(!Acteur->isClimbing)
    {

        InitGlimbing( SpeedX ,  SpeedY , Acteur,Tile );

    }
    else //If the *Acteur is already on the Ladder
    {   //Her is Climbing
        if(Acteur->isClimbing )
        {
            //TO ladder
            if(Acteur->isLadder)
            {
                
                MoveToLadder( SpeedX ,  SpeedY , Acteur);

                //manage the hero comes Up the ladder 
                if(*SpeedY >0)
                {
                    Acteur->Offset = Vector2(-TILEW/2,1);

                }else if(*SpeedY <0)
                {
                    Acteur->Offset = Vector2(-TILEW/2,-TILEH);
                }

                tile = GetTile( Vector2Add( Acteur->Position ,Acteur->Offset)) ;
                
                if(tile !=LADER && *SpeedY <0  && tile!= WALL)
                {
                    UpToExitLadder(SpeedX ,  SpeedY , Acteur);
                    return ;
                } else  if(tile !=LADER && *SpeedY <0  && tile== WALL)
                {
                    Acteur->Position.y =TOldY;
                }
                
                
                
                 if (tile !=LADER && *SpeedY >0)
                {
                    DownExitToLadder(SpeedX,SpeedY,Acteur , tile) ;

                    return;
                }
                
                //Check Left
                if(*SpeedX <0)
                {
                    Acteur->Offset = Vector2(-TILEW,-TILEH/2);

                  //Check Right   
                }else if(*SpeedX >0)
                {
                    Acteur->Offset = Vector2(0,-TILEH/2);
                }
    
                tile = GetTile( Vector2Add( Acteur->Position ,Acteur->Offset)) ;

                if(tile == -1)
                {
                    LeftAndRightExitToLadder(SpeedX ,  SpeedY , Acteur);
                    return;
                }
                else if(tile ==STICK)
                {

                    AppliqueAnimation(ANIMATIONGLIMBINGSTICK,3,Acteur) ;
                    Acteur->isClimbingStick = true ;
                    Acteur->isLadder = false ;
                    return ;
                }

              return ;  
            }
            else  if(Acteur->isClimbingStick)//thne player Glimbing in the Stick
            {
                VeloCityUpdate(SpeedX ,SpeedY ,Acteur) ;
                
                Acteur->Offset = Vector2(-TILEW/2 ,-TILEH/2);

                //Save Old Position.y *Acteur
                float oldx = Acteur->Position.x ;
                
                //Apply the new position to the *Acteur
               // Acteur->Offset = Vector2Zero ;
                int TH = ceil((Acteur->Position.y + Acteur->Offset.y)/TILEH);
                Acteur->Position.y =TH*TILEH ;
        
                Acteur->Position.x += Acteur->Velocity.x  * 0.014 ;
                
                //Check is Collision
                if (CheckCollision(Acteur,false))
                {
                    ExitToStick(Acteur) ;
                    return;
                }else
                {
                   //Left
                   
                    tile  = GetTile(Vector2Add( Acteur->Position , Acteur->Offset));
                    
                    
                    if( tile !=STICK )
                    {
                     ExitToStick(Acteur) ;
                        return;
                    }
                }
                return ;
            }
            
        }   
    } 
}

void InitGlimbing(float *SpeedX , float *SpeedY , struct GameObject *Acteur , int Tile)
{
    
    Acteur->Velocity = Vector2 ;

    //Change Animation
    if(Tile == LADER && *SpeedY!=0)
    {
        AppliqueAnimation(ANIMATIONGLIMBINGLADER,2,Acteur) ;
        Acteur->isLadder = true ;
        Acteur->isClimbingStick = false;
        //State Change
        Acteur->isClimbing = true ;
        Acteur->isGround = false ;

    }else if(Tile == STICK)
    {
        AppliqueAnimation(ANIMATIONGLIMBINGSTICK,2,Acteur) ;
        Acteur->isClimbingStick = true ;
        Acteur->isLadder = false;
        //State Change
        Acteur->isClimbing = true ;
        Acteur->isGround = false ;
    }
    
    //If the day comes down the ladder
    int TL = ceil((  Acteur->Position.x  + -(TILEW/2)  ) / TILEW ) ;
    //Apply the new position to the *Acteur
    Acteur->Position.x = TL * TILEW ; ;  
    return ;
}

void MoveToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
    VeloCityUpdate(SpeedX,SpeedY,Acteur) ;

     //Save Old Position.x 
    int OldX = Acteur->Position.x ;

    //Move to *Acteur
    if(*SpeedX!=0)
    {
        Acteur->Position.x += Acteur->Velocity.x  * 0.014 ;

    }else if(*SpeedX == 0)
    {
        Acteur->Velocity.x = 0;

    }
     if(*SpeedY !=0)
    {
        Acteur->Position.y += Acteur->Velocity.y  * 0.014 ;

    }else if (*SpeedY == 0)
    {
        Acteur->Velocity.y =0 ;
    }
    //Check is Collision
    if (CheckCollision(Acteur,false))
    {
        /*Move Postion.x to oldX Position.x */
        Acteur->Position.x = OldX ;
        /*Rezt Velocity Axe X*/
        Acteur->Velocity.x = 0 ;
    }

    return ;
}

void UpToExitLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
    AppliqueAnimation(ANIMATIONIDLE,2,Acteur) ;
    
    Acteur->Offset = Vector2(-TILEW/2 ,-TILEH/2) ;

    int Tile = GetTile( Vector2Add( Acteur->Position ,Acteur->Offset)) ;
                
    if(Tile !=LADER )
    {
        //Calculates the position of the *Acteur at the exit of the Ladder
        int TL = ceil((Acteur->Position.x + Acteur->Offset.x)/TILEW);
        int TH = ceil((Acteur->Position.y + Acteur->Offset.y)/TILEH);
        //Apply the new position to the *Acteur
        Acteur->Position =Vector2(TL*TILEW,TH*TILEH);

        //They say the hero doesn’t climb
        Acteur->isClimbing = false ;
        Acteur->isLadder = false ;
    }
   

    return;
}

void DownExitToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur,int Tile)
{
   
    AppliqueAnimation(ANIMATIONIDLE,2,Acteur) ;
    
    //Calculates the position of the *Acteur at the exit of the Ladder
    int TL = ceil((Acteur->Position.x + Acteur->Offset.x)/TILEW);
    int TH = ceil((Acteur->Position.y + Acteur->Offset.y)/TILEH)-1;
    //Apply the new position to the *Acteur
    Acteur->Position =Vector2(TL*TILEW,TH*TILEH);

    //They say the hero doesn’t climb
    Acteur->isClimbing = false ;
    Acteur->isLadder = false ;
    return;
}
void LeftAndRightExitToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
    //manage if the hero goes out to the right or left of the ladder
    AppliqueAnimation(ANIMATIONFALL,3,Acteur) ;

    Acteur->isClimbing = false ;
    Acteur->isLadder = false ;
    Acteur->isGround = false ;
    return;
}

void ExitToStick( struct GameObject *Acteur)
{
    AppliqueAnimation(ANIMATIONFALL,3,Acteur) ;

    Acteur->isClimbingStick = false ;
    Acteur->isGround = false ;
    Acteur->isClimbing = false ;
    Acteur->Position.y +=8;
    return;
}
void VeloCityUpdate(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
    //Update Velocity
    Acteur->Velocity.x += *SpeedX ;
    Acteur->Velocity.y += *SpeedY ;
    
    //Fixe Max Velocity
    /*Fixe Axe X Velocity*/
    if ( Acteur->Velocity.x > Acteur->MaxSpeed )
    {
         Acteur->Velocity.x = Acteur->MaxSpeed;

    }else if ( Acteur->Velocity.x < -Acteur->MaxSpeed )
    {
        Acteur->Velocity.x = -Acteur->MaxSpeed;
    }
    
     /*Fixe Axe Y Velocity*/
    if ( Acteur->Velocity.y > Acteur->MaxSpeed )
    {
        Acteur->Velocity.y = Acteur->MaxSpeed;

    }else  if ( Acteur->Velocity.y < -Acteur->MaxSpeed )
    {
        Acteur->Velocity.y = -Acteur->MaxSpeed;
    }
    
  return;
}