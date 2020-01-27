#include <raylib.h>
#include <stdio.h>
#include "main.h"
//Var BLoc Destroy & Build

struct Bloc
{
    Vector2 BlocPos;
    float TimeBloc;
    int CurentImg ;
    bool isActive;

    bool isBuild;
    float TimeToRebuild;
};




struct Bloc blocListe[10] ={0};
int ContBlocListe =0 ;
int AnimationBloc[5]={0};


void DestroyBloc(Vector2 PosB )
{
    int Tile = GetTile(PosB);
    if( Tile!= LADER && Tile != STICK && Tile!=-1 )
    {
        for (int i = 0; i < 10; i++)
        {
            if(!blocListe[i].isActive)
            {
                PlayFx(0);
                struct Bloc B ;
                B.BlocPos = PosB ;
                B.TimeBloc = 0 ;
                B.TimeToRebuild =0;
                B.CurentImg = 0 ;
                B.isActive = true ;
                B.isBuild = false;

                blocListe[i] = B;
                return;

            }
        }
    }
   
}

void UpdateBloc()
{
   int curentImgP;
    for (int i = 0; i < 10 ; i++)
    {
        if(blocListe[i].isActive)
        {
            
            //Re Build BLOC

            if(blocListe[i].isBuild == true)
            {
                
                if(blocListe[i].TimeToRebuild >=10 )
                {
                    
                    if(blocListe[i].TimeBloc >=1)
                    {
                        blocListe[i].TimeBloc = 0;
                        blocListe[i].CurentImg -=1;
                        if(blocListe[i].CurentImg <0)
                        {
                            curentImgP = WALL;
                            blocListe[i].isActive = false ;
                            SetTile(blocListe[i].BlocPos ,curentImgP);
                        }
                        else
                        {
                            curentImgP = AnimationBloc[blocListe[i].CurentImg] ;
                            SetTile(blocListe[i].BlocPos ,curentImgP);
                        }
                    }else
                    {
                        blocListe[i].TimeBloc +=0.15f;
                    }
                    
                    
                }else
                {
                    blocListe[i].TimeToRebuild +=0.015f; 
                }
                
            }
            //Destroy BLoc    
            else if(blocListe[i].isBuild == false)
            {
               
                if(blocListe[i].TimeBloc >=1)
                {
                    curentImgP =AnimationBloc[ blocListe[i].CurentImg] ;

                    blocListe[i].TimeBloc =0 ;

                    blocListe[i].CurentImg +=1;

                    //Check No Max Img
                    if(blocListe[i].CurentImg >3)
                    {
                        blocListe[i].CurentImg =3;
                        curentImgP =-1;
                        blocListe[i].isBuild = true;
                        blocListe[i].TimeToRebuild = 0;
                        blocListe[i].TimeBloc =0;
                        SetTile(blocListe[i].BlocPos ,curentImgP);
                    }else
                    {
                        curentImgP = AnimationBloc[blocListe[i].CurentImg] ;
                        SetTile(blocListe[i].BlocPos ,curentImgP);
                    }
                }else
                {
                    blocListe[i].TimeBloc +=0.05f;
                }
                
                
                
                
            }
            
            
        
        }
       
    }
    
}

void InitAnimationBloc()
{
    AnimationBloc[0] =94 ;
    AnimationBloc[1] =93 ;
    AnimationBloc[2] =92 ;
    AnimationBloc[3] =91 ;
    printf("ANIMATION BLOC DESTROY CHARGER \n") ;
}