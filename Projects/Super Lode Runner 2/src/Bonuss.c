#include <raylib.h>
#include <raymath.h>
#include "main.h"
#include "Sound.h"

GameObject bonus[10]={0};
int NumberBonus =0;

void InitBonus(GameObject *liste[],Vector2 Spawn,int bonusImg)
{  
    
   NumberBonus +=1;
   bonus[NumberBonus].isActive = true;
   bonus[NumberBonus].Position.x = Spawn.x ;
   bonus[NumberBonus].Position.y = Spawn.y ;
    //Init speed 
   bonus[NumberBonus].Speed = 0 ;
   bonus[NumberBonus].MaxSpeed =0 ;
   bonus[NumberBonus].Velocity = Vector2Zero;

   bonus[NumberBonus].isGround = true;
   bonus[NumberBonus].isClimbing = false;

   bonus[NumberBonus].Offset = Vector2Zero ;

   bonus[NumberBonus].Animation.Pause = true ;
   bonus[NumberBonus].Animation.Frame[0][0] = bonusImg;

    AppliqueAnimation( 0 , 1 , &bonus[NumberBonus] ) ;
    
    liste[(NumberBonus+2)] = &bonus[NumberBonus] ;
}

bool CheckColBonus(GameObject *Acteur)
{
    int L = ceil( Acteur->Position.x / TILEW ) ;
    int H = ceil ( Acteur->Position.y / TILEH ) ;
    
    for (int i = 0 ; i < 10 ; i++)
    {
        if(bonus[i].isActive == true)
        {
            int Bl = ceil( bonus[i].Position.x/TILEW );
            int BH = ceil ( bonus[i].Position.y/TILEH ) ;

            if(Bl == L && BH == H){
                bonus[i].isActive = false;
                PlayFx(1);
                SetScore(GetScore + 100) ;
                return true ;

            }
            
        } 
    }
    return 0;
}