#include <raylib.h>
#include <raymath.h>


#define Rectangle(x,y,w,h)   (Rectangle){x,y,w,h}
#define Vector2(x,y)   (Vector2){x,y}
#define Vector2Zero  Vector2(0,0)
#define Color(r,g,b,a)  (Color){r,g,b,a}  
#define max(a, b)         ((a) > (b) ? (a) : (b))
#define min(a, b)         ((a) < (b) ? (a) : (b))
#define Scale(l,h) (Scale){l,h}
#define TILEH  17
#define TILEW  16
#define MAPRESOW 512
#define MAPRESOH 306

typedef struct GameObject
{
    //MOOV
    float Speed  ;
    Vector2 Velocity  ;
    float MaxSpeed  ;
    Vector2 Position  ;

 
//Animation
    int Frame[10][10] ;
    int MaxFrame  ;
    int NumeroAnimation  ;
    int CurentFrame  ;
    bool Flip  ;

  //STATES
  bool isClimbing ;
  bool isLadder ;
  bool isClimbingStick ;
  bool isFall ;
  bool isGround ;

}GameObject;


typedef struct Scale
{
    float l ;
    float h ;
}Scale;


//Map
void InitMap() ;
void DrawMap(Texture2D tilset, Rectangle ListeRectangle[]);
int GetTile(Vector2 Pposition) ;
bool SetTile(Vector2 Pposition , int Ptile) ; 

//PLAYER
void InitPlayer();
Vector2 InputManager();
void UpdateAnimation();
void DrawPlayer(Texture2D tilset ,Rectangle ListeRectangle[]);
