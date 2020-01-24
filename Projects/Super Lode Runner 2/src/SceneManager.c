#include "main.h"
#include <raylib.h>
#include <stdio.h>
#include "Sound.h"




bool LoadScene( int NumeroScene ,int*SceneM)
{
    if(NumeroScene >=Menu && NumeroScene <=GamePlay)
    {
        *SceneM = NumeroScene ;
        if(NumeroScene == GamePlay){
           PlayMusique(3); 
        }

        return true;
    }
  

    printf("NuMeroScene invalide ");
    return false ;

}
