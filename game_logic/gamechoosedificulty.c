#include "gamechoosedificulty.h"
#include "gamesettings.h"
#include "gamechooselevel.h"
#include "gamestartlevel.h"
#include "game.h"

void setDificultyAndGoToTheNextLevel_gamelogic()
{
    saveActionStateAsDificulty();
    gameStartLevel();
}

void backToPreviousLevel_gamelogic()
{
    gameChooseLevel();
}

void showPreviousDificulty_gamelogic()
{
    if(!isGameActionEqual(GAMEDIFICULTY_TURTLE))
    {
        previousGameAction();
    }
}

void showNextDificulty_gamelogic()
{
    if(!isGameActionEqual(GAMEDIFICULTY_ASIAN))
    {
        nextGameAction();
    }
}


void gameChooseDificulty()
{
    setGameLevel(GAMEMENU_GAMEDIFICULTY,
                 GAMEDIFICULTY_NORMAL,
                 &showPreviousDificulty_gamelogic,
                 &showNextDificulty_gamelogic,
                 &setDificultyAndGoToTheNextLevel_gamelogic,
                 &backToPreviousLevel_gamelogic,
                 &noAction);
}
