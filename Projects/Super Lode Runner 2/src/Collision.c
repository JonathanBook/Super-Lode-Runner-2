#include "main.h"
#include <raylib.h>
#include <math.h>
#include <raymath.h>


//Check the different collisions the hero may encounter
bool CheckCollision(GameObject *Acteur ,bool IsCheckGround)
{
    Acteur->Offset  = Vector2(-TILEW/2,1);//Ground Offset

    if(!IsCheckGround)
    {
        if(Acteur->Velocity.x <0  )
        {
            Acteur->Offset = Vector2(-TILEW,-TILEH/2); //OffSet Left

        }else if(Acteur->Velocity.x >0  )
        {
            Acteur->Offset = Vector2(1,-TILEH/2);//Offset Right 

        }

        int tile = GetTile( Vector2Add(Acteur->Position ,Acteur->Offset) ) ;

        if ( tile !=-1 && tile !=LADER && tile!=STICK  )
        {
            return true ;
        }
        return false ;
    }
    else if(IsCheckGround)
    {
        int tile = GetTile( Vector2Add(Acteur->Position ,Acteur->Offset) ) ;

        if (tile == WALL || tile == LADER ) 
        {
            return true ;
        }
         return false;  
    }
    return false ;
}