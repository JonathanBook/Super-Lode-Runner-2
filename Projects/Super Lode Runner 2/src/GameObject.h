#include <raylib.h>
typedef struct GameObject
{
    //MOOV
    float Speed  ;
    Vector2 Velocity  ;
    float MaxSpeed  ;
    Vector2 Position  ;
    Vector2 Offset ;

   
    struct Animation{
    int Frame[10][10] ;
    int MaxFrame  ;
    int NumeroAnimation  ;
    int CurentFrame  ;
    float TimeAnimation ;
    bool Pause  ;
    }Animation ;   
    

    bool Flip  ;

  //STATES
    bool isActive;
    bool isClimbing ;
    bool isLadder ;
    bool isClimbingStick ;
    bool isFall ;
    bool isGround ;
  
  char Name[10];
  
   

}GameObject;

void DrawGameObject(Texture2D tilset ,Rectangle ListeRectangle[],GameObject*liste[]);