#include "main.h"
#include <raylib.h>

//Change the animation curent to play
void AppliqueAnimation(int NumeroAnimation , int MaxFrame, struct GameObject *Acteur)
{
    if(NumeroAnimation == AnNul)
        return;

    if(Acteur->Animation.NumeroAnimation != NumeroAnimation )
    {
        Acteur->Animation.NumeroAnimation = NumeroAnimation ;
        Acteur->Animation.MaxFrame = MaxFrame ;
    }
    
}
//play animation
void UpdateAnimation(struct GameObject *Acteur)

{ 
    //if the velocity and equal zero and that the current animation and diferent of the idle but lamination on pause
    if(Acteur->Velocity.x == Vector2Zero.x && Acteur->Velocity.y == Vector2Zero.y && Acteur->Animation.NumeroAnimation != ANIMATIONIDLE)
    {
        Acteur->Animation.Pause = true;
        return;
      
      //Otherwise the animation is not on pause
    }else if(Acteur->Velocity.x == Vector2Zero.x && Acteur->Velocity.y == Vector2Zero.y)
    {
        Acteur->Animation.Pause = false;
    }
    
    //Update Timer
    Acteur->Animation.TimeAnimation +=0.05 ;

    //Change Frame is rezet Timer
    if(Acteur->Animation.TimeAnimation >=1)
    {
        Acteur->Animation.TimeAnimation = 0 ;
        Acteur->Animation.CurentFrame ++ ;
    }
    //if the image counter is at the maximum of available image we reset the counter to zero
    if(Acteur->Animation.CurentFrame >= Acteur->Animation.MaxFrame)
        Acteur->Animation.CurentFrame = 0 ;
    
}