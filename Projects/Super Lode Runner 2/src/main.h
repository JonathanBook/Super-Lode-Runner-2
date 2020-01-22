#include <raylib.h>
#include <raymath.h>

#define SCREENH 240
#define SCREENW 256
#define Rectangle(x,y,w,h)   (Rectangle){x,y,w,h}
#define Vector2(x,y)   (Vector2){x,y}
#define Vector2Zero  Vector2(0,0)
#define Color(r,g,b,a)  (Color){r,g,b,a}  
#define max(a, b)         ((a) > (b) ? (a) : (b))
#define min(a, b)         ((a) < (b) ? (a) : (b))
#define Scale(l,h) (Scale){l,h}


//PLAYER DEFINE
//Define the dimensions of a tile
#define PLAYERTILEW 16
#define PLAYERTILEH 17

//Definition of animation
#define ANIMATIONIDLE 0
#define ANIMATIONLEFT 1
#define ANIMATIONRIGHT 1
#define ANIMATIONGLIMBINGLADER 2
#define ANIMATIONGLIMBINGSTICK 4
#define ANIMATIONFALLSTICK 5
#define ANIMATIONFALL 6
#define AnNul -1 

//MAP DEFINE
#define TILEH  17
#define TILEW  16
#define MAPRESOW 512
#define MAPRESOH 306
//Definition of the different tiles
#define WALL 85
#define LADER 73
#define STICK 75
//SceneManager
#define Menu 0 
#define GamePlay 1

typedef struct Animation
{
    //Animation
    int Frame[10][10] ;
    int MaxFrame  ;
    int NumeroAnimation  ;
    int CurentFrame  ;
    float TimeAnimation ;
    bool Pause  ;
}Animation;

typedef struct SceneManager
{
    int CurentScene ;
   
}SceneManager;

typedef struct GameObject
{
    //MOOV
    float Speed  ;
    Vector2 Velocity  ;
    float MaxSpeed  ;
    Vector2 Position  ;
    Vector2 Offset ;

    struct Animation Animation ;   

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


//map.c
void InitMap() ;
void DrawMap(Texture2D tilset, Rectangle ListeRectangle[]);
int GetTile(Vector2 Pposition) ;
bool SetTile(Vector2 Pposition , int Ptile) ; 

//player.c
void InitPlayer();
Vector2 InputManager();
void DrawPlayer(Texture2D tilset ,Rectangle ListeRectangle[]);

//Glimbing.c
void Glimbing(float *SpeedX , float *SpeedY , GameObject *Acteur,int Tile) ;
void ExitToStick( struct GameObject *Acteur) ;
bool CheckIsGlimbing(float *SpeedX , float *SpeedY , GameObject *Acteur);
//Animation.c
void AppliqueNewAnimation(int NumeroAnimation , int MaxFrame,struct GameObject *Acteur);
void UpdateAnimation(struct GameObject *Acteur);

//Collision.c
bool CheckCollision(GameObject *Acteur,bool IsCheckGround);