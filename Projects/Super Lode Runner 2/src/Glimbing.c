#include "main.h"
#include <raylib.h>
#include <math.h>
#include <raymath.h>
#include <stdio.h>

void InitGlimbing(float *SpeedX , float *SpeedY , struct GameObject *Acteur);
void MoveToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur);
void UpToExitLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur);
void DownExitToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur);
void LeftAndRightExitToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur);
void VeloCityUpdate(float *SpeedX , float *SpeedY , struct GameObject *Acteur);


//TODO: Messy function to review
//Managed the ascent and descent to the ladder
void ClimbingLadder(float *SpeedX , float *SpeedY,struct GameObject  *Acteur)
{   
    int tile ;
    //Init Velocity
   VeloCityUpdate(SpeedX ,  SpeedY , Acteur);

    //If the day is not on the Ladder
    if(!Acteur->isClimbing)
    {

        InitGlimbing( SpeedX ,  SpeedY , Acteur);

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

                Acteur->Offset = Vector2(-8,-8);
                tile = GetTile( Vector2Add( Acteur->Position ,Acteur->Offset)) ;

                if(*SpeedY < 0 && tile !=LADER)
                {
                    UpToExitLadder(SpeedX ,  SpeedY , Acteur);
                    return ;
                }
                else
                {
                     //manage the hero comes Down the ladder  
                    Acteur->Offset = Vector2(0,1);
                    tile = GetTile( Vector2Add( Acteur->Position ,Acteur->Offset)) ;

                    if(*SpeedY > 0 && tile !=LADER)
                    {
                        DownExitToLadder(SpeedX ,  SpeedY , Acteur);
                        return ;
                    }
                    else
                    {
                        //Check Left
                        Acteur->Offset = Vector2(-16,-8);
                        tile = GetTile( Vector2Add( Acteur->Position ,Acteur->Offset)) ;

                        //Check Right
                        Acteur->Offset = Vector2(1,-8);
                        int tile2 = GetTile( Vector2Add( Acteur->Position ,Acteur->Offset)) ;

                        if(Acteur->Velocity.x <0 && tile == -1  || Acteur->Velocity.x >0 && tile2 == -1)
                        {
                           LeftAndRightExitToLadder(SpeedX ,  SpeedY , Acteur);
                           return;
                        }
                        else
                        {
                            //Check Stick Collision 
                            //Left
                            Acteur->Offset = Vector2(-TILEW,0);
                            tile = GetTile( Vector2Add( Acteur->Position ,Acteur->Offset)) ;
                            //Right
                            Acteur->Offset = Vector2(TILEW/2,0);
                            int tile2 = GetTile( Vector2Add( Acteur->Position ,Acteur->Offset)) ;

                            if(Acteur->Velocity.x <0 && tile ==STICK || Acteur->Velocity.x >0 && tile2 == STICK)
                            {
                            
                                AppliqueAnimation(ANIMATIONGLIMBINGSTICK,3,Acteur) ;
                                Acteur->isClimbingStick = true ;
                                Acteur->isLadder = false ;
                                return ;
                                    
                            }
                           
                        }   
                    }
                }
              return ;  
            }
            else  if(Acteur->isClimbingStick)//thne player Glimbing in the Stick
            {
               Acteur->Velocity.y = 0 ;
                //Save Old Position.y *Acteur
                float oldx = Acteur->Position.x ;
                
                //Apply the new position to the *Acteur
                Acteur->Offset = Vector2Zero ;
                int TH = ceil((Acteur->Position.y + Acteur->Offset.y)/TILEH);
                Acteur->Position.y =TH*TILEH ;
        
                Acteur->Position.x += Acteur->Velocity.x  * 0.014 ;
                
                //Check is Collision
                if (CheckCollision(Acteur,false))
                    ExitToStick(Acteur) ;
                    return;
                
                //Left
                Acteur->Offset = Vector2(-TILEW,0);
                tile  = GetTile(Vector2Add( Acteur->Position , Acteur->Offset));
                //Right
                Acteur->Offset = Vector2(1,0);
                int tile2  = GetTile(Vector2Add( Acteur->Position , Acteur->Offset));
                
                if(Acteur->Velocity.x <0 && tile !=STICK  || Acteur->Velocity.x >0 && tile2 !=STICK)
                {
                   ExitToStick(Acteur) ;
                    return;
                }
                   
                return ;
            }
            
        }   
    } 
}

void InitGlimbing(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
    //Change Animation
    AppliqueAnimation(ANIMATIONGLIMBINGLADER,2,Acteur) ;
    //State Change
    Acteur->isClimbing = true ;
    Acteur->isLadder = true ;
    Acteur->isGround = false ;

    //If the day comes down the ladder
    int TL = ceil((  Acteur->Position.x  + -(TILEW/2)  ) / TILEW ) ;
    TL = TL * TILEW ;
    //Apply the new position to the *Acteur
    Acteur->Position.x = TL ;  

    return ;
    
}

void MoveToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
     //Save Old Position Acteur
    Vector2 Old = Acteur->Position ;

    //Move to *Acteur
    Acteur->Position.y += Acteur->Velocity.y * 0.014 ;
    Acteur->Position.x += Acteur->Velocity.x  * 0.014 ;

    //Check is Collision
    if (CheckCollision(Acteur,false))
    {
        //Move Postion.x to old Position.x
        Acteur->Position.x = Old.x ;
        //Acteur->Velocity = Vector2Zero ;
    }
    return ;
}

void UpToExitLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
    AppliqueAnimation(ANIMATIONIDLE,2,Acteur) ;
    
    Acteur->Offset = Vector2(-8,-8);
    //Calculates the position of the *Acteur at the exit of the Ladder
    int TL = ceil((Acteur->Position.x + Acteur->Offset.x)/TILEW);
    int TH = ceil((Acteur->Position.y + Acteur->Offset.y)/TILEH);
    //Apply the new position to the *Acteur
    Acteur->Position =Vector2(TL*TILEW,TH*TILEH);

    //They say the hero doesn’t climb
    Acteur->isClimbing = false ;
    Acteur->isLadder = false ;
    Acteur->Offset = Vector2Zero ;
    return;
}

void DownExitToLadder(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
    AppliqueAnimation(ANIMATIONIDLE,2,Acteur) ;

    Acteur->Offset = Vector2(0,1);
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

void ClimbingStick(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
    AppliqueAnimation(ANIMATIONGLIMBINGSTICK,2,Acteur);
    
  //  VeloCityUpdate(SpeedX,SpeedY,Acteur);
    
    Acteur->isClimbing = true;
    Acteur->isClimbingStick = true;
    Acteur->isLadder = false ;
    Acteur->isGround = false ;
    Acteur->Velocity = Vector2Zero ;
    ClimbingLadder(SpeedX ,SpeedY ,Acteur);
    return;
}
void ExitToStick( struct GameObject *Acteur)
{
    AppliqueAnimation(ANIMATIONFALL,3,Acteur) ;

    Acteur->isClimbingStick = false ;
    Acteur->isGround = false ;
    Acteur->isClimbing = false ;
    return;
}
void VeloCityUpdate(float *SpeedX , float *SpeedY , struct GameObject *Acteur)
{
    //Update Velocity
    Acteur->Velocity.x += *SpeedX ;
    Acteur->Velocity.y += *SpeedY ;
    
    //Fixe Speed Max Velocity
    if ( Acteur->Velocity.x > Acteur->MaxSpeed )
        Acteur->Velocity.x = Acteur->MaxSpeed;
        
    if ( Acteur->Velocity.y > Acteur->MaxSpeed )
        Acteur->Velocity.y = Acteur->MaxSpeed;
  
}