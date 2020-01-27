#include <raylib.h>
#include <stdio.h>
#include "main.h"

#define LEFT Vector2(-1,0)
#define RIGHT Vector2(1,0)

typedef  struct IA
{
    GameObject Object;
    Vector2 Direction;
} IA;

//de 0 a 11 reserver a ho jouer est ho bonus 
int CountEnemy =12 ;

//Enemy Liste 
IA EnemyList[9]={} ;

typedef enum State 
{
    CHECK ,
    FOLLOW 

}State;

//Compare de vector2 
bool Vector2Compare(Vector2 a ,Vector2 b)
{
    if(a.x == b.x && a.y == b.y)
        return true ;
    return false;
}

State EnemyState = CHECK ;

//Delcaration fonction
void InitEnemyInfo(IA *iA,GameObject *liste[],Vector2 Spawn);
void InitAnimationEnemy(IA *iA);


void InitEnemy(GameObject *liste[],Vector2 Spawn)
{
    InitAnimationEnemy(&EnemyList[CountEnemy - 12] );
    InitEnemyInfo(&EnemyList[CountEnemy - 12] ,liste,Spawn);
    
}

void InitEnemyInfo(IA *iA,GameObject *liste[],Vector2 Spawn)
{   
    //Limite Max Enemis to screen a 9
    if(CountEnemy >=20)
        return ;

    //Init position PlayerOne
    iA->Object.isActive = true ;
    iA->Object.Position = Spawn;
    //Init speed 
    iA->Object.Speed = 8 ;
    iA->Object.MaxSpeed = 40 ;
    iA->Object.Velocity = Vector2Zero;
    iA->Object.isGround = true;
    iA->Object.isClimbing = false;
    iA->Object.Offset = Vector2Zero ;
    iA->Object.Animation.Pause = false ;
    iA->Direction = Vector2Zero ;
    liste[CountEnemy] = &iA->Object ;
   
    CountEnemy +=1;
}

void InitAnimationEnemy(IA *iA)
{
    //Idle Position
   iA->Object.Animation.Frame[0][0] = 3;
   iA->Object.Animation.Frame[0][1] = 2;
    printf("ANIMATION IDLE CHARGER \n") ;
   //Walk Left Right
    iA->Object.Animation.Frame[1][0] = 17 ;
    iA->Object.Animation.Frame[1][1] = 16;
    iA->Object.Animation.Frame[1][2] = 15;
    printf("ANIMATION LEFT AND RIGHT CHARGER \n") ;
    //Climbing LADER
    iA->Object.Animation.Frame[2][0] = 26 ;
    iA->Object.Animation.Frame[2][1] = 27;

    printf("ANIMATION GLIMP CHARGER \n") ;
    //And Climbing
    iA->Object.Animation.Frame[3][0] = 41 ;
    iA->Object.Animation.Frame[3][1] = 40 ;
    iA->Object.Animation.Frame[3][2] = 39 ;
     printf("ANIMATION GLIMP AND CHARGER \n") ;
    //Climbing Stick
    iA->Object.Animation.Frame[4][0] = 58 ;
    iA->Object.Animation.Frame[4][1] = 57 ;
    iA->Object.Animation.Frame[4][2] = 56 ;
    iA->Object.Animation.Frame[4][2] = 55 ;
     printf("ANIMATION HUP CHARGER \n") ;
    //Fall Climbing Stick
    iA->Object.Animation.Frame[5][0] = 52 ;
    iA->Object.Animation.Frame[5][1] = 51 ;
    printf("ANIMATION CHUTE STICK CHARGER \n") ;
    //Fall
    iA->Object.Animation.Frame[6][0] = 65 ;
    iA->Object.Animation.Frame[6][1] = 64 ;
    iA->Object.Animation.Frame[6][2] = 63 ;
    printf("ANIMATION CHUTE CHARGER \n") ;
    
}

void Ia(GameObject *Player)
{
     
    for (int i = 0; i < 9; i++)
    {
        float distance = Vector2Distance( EnemyList[i].Object.Position , Player->Position);
       
        switch (EnemyState)
        {
        case CHECK :
 
            MouvActeur(EnemyList[i].Object.Speed * EnemyList[i].Direction.x,
                EnemyList[i].Object.Speed * EnemyList[i].Direction.y,
                &EnemyList[i].Object);

            UpdateAnimation(&EnemyList[i].Object);


             if(CheckCollision(&EnemyList[i].Object,false) && Vector2Compare(EnemyList[i].Direction , RIGHT) ||Vector2Compare(EnemyList[i].Direction,Vector2Zero))
            {   
                EnemyList[i].Object.Flip = false;
                EnemyList[i].Direction = LEFT ;
                return;  
            }else if(CheckCollision(&EnemyList[i].Object,false) && Vector2Compare(EnemyList[i].Direction , LEFT))
            {
                EnemyList[i].Object.Flip = true;
                EnemyList[i].Direction = RIGHT ;
                return;
            }

            if(!EnemyList[i].Object.isClimbing && GetTile(Vector2Add(EnemyList[i].Object.Position , Vector2(-8,8)))== LADER)
            {
                
                EnemyList[i].Direction = Vector2(0,1);
                
            }else if(!EnemyList[i].Object.isClimbing && Vector2Compare(EnemyList[i].Direction, Vector2(0,1)))
            {
                 EnemyList[i].Object.Flip = false;
                EnemyList[i].Direction = LEFT ;
            }

            break;
        
        case FOLLOW :
            break;

        default :
            break;    

        
            
        }
    }
}