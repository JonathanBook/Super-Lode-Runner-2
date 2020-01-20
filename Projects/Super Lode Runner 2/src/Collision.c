#include "main.h"
#include <raylib.h>
#include <math.h>
#include <raymath.h>


//Check the different collisions the hero may encounter
bool CheckCollision(GameObject *Acteur ,bool IsCheckGround)
{
    Acteur->Offset  = Vector2(-8,1);//Ground Offset

    if(Acteur->Velocity.x <0 && !IsCheckGround )
       Acteur->Offset = Vector2(-TILEW,-8); //OffSet Left

    if(Acteur->Velocity.x >0 && !IsCheckGround )
        Acteur->Offset = Vector2(1,-8);//Offset Right     
  
    int tile = GetTile( Vector2Add(Acteur->Position ,Acteur->Offset) ) ;
    
    if ( tile != 0 && tile!=-1 && !IsCheckGround && tile!=LADER && tile!=STICK  )
        return true ;

    if (tile != 0 && tile!=-1 && IsCheckGround  && tile!=STICK ) 
        return true ;   

    return false    ;
}