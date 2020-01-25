#include <raylib.h>
#include "GameObject.h"
#include <raymath.h>

#define SCREENH 240
#define SCREENW 400
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


//Glimbing.c
bool CheckIsGlimbing(float *SpeedX , float *SpeedY , GameObject *Acteur);

//Animation.c
void AppliqueNewAnimation(int NumeroAnimation , int MaxFrame, GameObject *Acteur);
void UpdateAnimation( GameObject *Acteur);

//Collision.c
bool CheckCollision(GameObject *Acteur,bool IsCheckGround);

//Bonus.c 
void InitBonus(GameObject *liste[],Vector2 Spawn,int bonusImg);
bool CheckColBonus(GameObject *Acteur);
//main.c
void DefineGameObjectTable(GameObject *liste[]);
void InitMapExecute();

//SceneManager.c
bool LoadScene( int NumeroScene ,int*SceneM);
//MovActeur.c
void MouvActeur(float SpeedX , float SpeedY , GameObject *Acteur );
//GameManager.c
void InitGamePlay();
int SetScore(int Points);
int SetBestScore(int Points);
int GetScore();
int GetBestScore();
bool GamePlayPause();
bool GetPause();