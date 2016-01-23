#pragma once
#include <stdlib.h>
#include "game.h"
#include "gamestate.h"

void goToChooseLevelState_gamelogic(Game* game)
{
    srand(game->time);
    gameChooseLevel(game);
}

void gameInit(Game* game)
{
    setGameLevel(game,
                 GAMEMENU_GAMENAME,
                 GAMEINFO_PRESSKEY,
                 &goToChooseLevelState_gamelogic,
                 &goToChooseLevelState_gamelogic,
                 &goToChooseLevelState_gamelogic,
                 &goToChooseLevelState_gamelogic,
                 &noAction);
}
