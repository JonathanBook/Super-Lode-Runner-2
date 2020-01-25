#include <raylib.h>
#include "main.h"
//#include "GameObject.h"
bool CheckGround(GameObject *Acteur);

int Gravity = 10 ;

void MouvActeur(float SpeedX , float SpeedY , GameObject *Acteur )
{
    
    CheckColBonus(Acteur);

    if( CheckIsGlimbing(&SpeedX,&SpeedY,Acteur))
    {
       return ;

    } 
   else if(!Acteur->isClimbing)
   {   //Check Is Player Touch Ground
       Acteur->isGround = CheckGround(Acteur);
       if(Acteur->isGround)
       {
           Acteur->isGround = true ;
           //Fixe Velocity.X
            if(SpeedX == 0)
            {
                Acteur->Velocity.x = 0 ;
                AppliqueAnimation(ANIMATIONIDLE,2,Acteur) ;
                return;
            }
 
        }
        else 
        {
           
           Acteur->Velocity.y += Gravity ;
           //TODO: Play Sound Fall
            PlayFx(4);
            //Fixe Max Speed and Axe Y
           if(Acteur->Velocity.y > Acteur->MaxSpeed)
           {
               Acteur->Velocity.y = Acteur->MaxSpeed;
           }

           //Move Player and Axe Y
           Acteur->Position.y += Acteur->Velocity.y * 0.014 ;

           //Check if we are playing the right animation
            AppliqueAnimation(ANIMATIONFALL ,3 , Acteur);

        } //End Gravity check
        
        //Fixe Max Speed and Axe X
         Acteur->Velocity.x += SpeedX  ;
        if(Acteur->Velocity.x > Acteur->MaxSpeed  )
        {
            Acteur->Velocity.x = Acteur->MaxSpeed ; 

        } else if(Acteur->Velocity.x < -Acteur->MaxSpeed  ) 
        {
            Acteur->Velocity.x = -Acteur->MaxSpeed ; 
        }

        //Save player position before moving 
        float oldx = Acteur->Position.x ;

        //Move Player and Axe X
        Acteur->Position.x += Acteur->Velocity.x * 0.014 ;

        //Check Collision new Possition
        if(CheckCollision(Acteur,false))
        {
            Acteur->Velocity.x = 0 ;
            Acteur->Position.x = oldx ;
            return ;
        }
       
        
        //Check if we are playing the right animation
        if(Acteur->isGround )
        {
            //TODO:Play sound Sound Walk
            PlayFx(3);
            AppliqueAnimation(ANIMATIONLEFT ,3 ,Acteur);
        }    
   }//End Check Glimbing
  
}

//Check if the hero hits the ground or not
bool CheckGround(GameObject *Acteur)
{
    if( CheckCollision(Acteur,true))
    {
        float pos = ceil( (Acteur->Position.y-10)/TILEH ) * TILEH ;
        Acteur->Position.y = pos  ;
        Acteur->Velocity.y =0 ;
        return true;
    }
  
    return false ;
    
}