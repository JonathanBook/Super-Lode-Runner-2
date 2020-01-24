#include <raylib.h>
#include "Sound.h"

void LoadMusique ();
void LoadFx ();

Music  Musique[6] ={0};
Sound  Fx[5] = {0};
int CurentMusic ;

void initSound()
{   
    InitAudioDevice();      // Initialize audio device
    LoadMusique();
    LoadFx ();
}



void LoadMusique ()
{
    
    Musique[0] = LoadMusicStream("Assets/Sounds/Music/Bonus.mp3");
    Musique[1] = LoadMusicStream("Assets/Sounds/Music/GameOver.mp3");
    Musique[2] = LoadMusicStream("Assets/Sounds/Music/Lvel Win.mp3");
    Musique[3] = LoadMusicStream("Assets/Sounds/Music/LevelMusic.ogg");
    Musique[4] = LoadMusicStream("Assets/Sounds/Music/BonusSpeedVersion.mp3");
}

void LoadFx ()
{
    Fx[0] = LoadSound("Assets/Sounds/Fx/BlocDestruction.mp3");
    Fx[1] = LoadSound("Assets/Sounds/Fx/BonusRecup.mp3");
    Fx[2] = LoadSound("Assets/Sounds/Fx/Bruit Pas.mp3");
    Fx[3] = LoadSound("Assets/Sounds/Fx/Bruit Pas2.mp3");
    Fx[4] = LoadSound("Assets/Sounds/Fx/BruitChute.mp3");
}

void SoundUpdate(bool Pause){


    UpdateMusicStream(Musique[CurentMusic]);
    if(Pause){
        if(IsMusicPlaying)
            PauseMusicStream(Musique[CurentMusic]);

    }else
    {
        if(!IsMusicPlaying)
           ResumeMusicStream(Musique[CurentMusic]);
        
    }
    

}

void PlayMusique(int i)
{
  
    CurentMusic = i ;
    PlayMusicStream(Musique[i]);
    SetMusicVolume(Musique[i],0.5f);
   
 
}

void PlayFx(int i)
{
   
    if(i==3 || i== 4){
        //if sound Equal 3 or 4 &  not playing 
        if(!IsSoundPlaying(Fx[i])){
            
            PlaySound(Fx[i]);
        }

    }else //if Different 3 or 4
    {
        PlaySoundMulti(Fx[i]);
    }
        
       
   
    
}