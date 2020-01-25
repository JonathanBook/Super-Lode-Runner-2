#include "main.h"

void RezetScore();
//Pause
bool isPause = false;

//Score
int TotalScore ;
int BestScore ;
int CurentStage ;
int MaximumStage ;



void InitGamePlay()
{
    RezetScore() ;
    InitMapExecute();
}

int SetScore(int Points)
{
    TotalScore = Points;
    return TotalScore ;
}

int SetBestScore(int Points)
{
    BestScore = Points ;
}

int GetScore()
{
    return TotalScore;
}

int GetBestScore()
{
    return BestScore;
}

void RezetScore()
{
    TotalScore = 0 ;
}

bool GamePlayPause()
{
    isPause = !isPause;
    return isPause ;
}

bool GetPause()
{
    return isPause ;
}