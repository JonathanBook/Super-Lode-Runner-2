#include <raylib.h>
#include <raymath.h>
#include <math.h>

#define SCREENH 240
#define SCREENW 256
#define Rectangle(x,y,w,h)   (Rectangle){x,y,w,h}
#define Vector2(x,y)   (Vector2){x,y}
#define Vector2Zero  Vector2(0,0)
#define Color(r,g,b,a)  (Color){r,g,b,a}  
#define max(a, b)         ((a) > (b) ? (a) : (b))
#define min(a, b)         ((a) < (b) ? (a) : (b))
#define Scale(l,h) (Scale){l,h}

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
#define BONUUSIMG 76



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
  //Scor
  int Points;
  int Value;
   

}GameObject;



typedef struct Scale
{
    float l ;
    float h ;
}Scale;

void InitPause();
//map.c
void InitMap(GameObject *l[]) ;
void DrawMap(Texture2D tilset, Rectangle ListeRectangle[]);
int GetTile(Vector2 Pposition) ;
bool SetTile(Vector2 Pposition , int Ptile) ; 

//player.c
void SelectedCountPlayer(int Count);
void InitPlayers(GameObject *liste[],Vector2 Spawn,int Player,int Tile);
Vector2 InputManager();
void DrawGameObject(Texture2D tilset ,Rectangle ListeRectangle[],GameObject*liste[]);

//Glimbing.c
void Glimbing(float *SpeedX , float *SpeedY , GameObject *Acteur,int Tile) ;
void ExitToStick(  GameObject *Acteur) ;
bool CheckIsGlimbing(float *SpeedX , float *SpeedY , GameObject *Acteur);
//Animation.c
void AppliqueNewAnimation(int NumeroAnimation , int MaxFrame, GameObject *Acteur);
void UpdateAnimation( GameObject *Acteur);

//Collision.c
bool CheckCollision(GameObject *Acteur,bool IsCheckGround);
//Bonus.c 
void InitBonus(GameObject *liste[],Vector2 Spawn,int bonusImg);
void DefineGameObjectTable(GameObject *liste[]);
int CheckColBonus(GameObject *Acteur);
bool LoadScene( int NumeroScene ,int*SceneM);
void MouvPlayer(float SpeedX , float SpeedY , GameObject *Acteur );
void InitMapExecute();