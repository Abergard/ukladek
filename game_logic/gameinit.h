#pragma once
#include <stdlib.h>
#include "game.h"
#include "gamestate.h"

void goToChooseLevelState_gamelogic(Game* game)
{
    if(game->menuState == GAMEEND_WIN)
    {
        gameStartLevel(game);
    }
    else
    {
        gameChooseLevel(game);
    }
}

void gameInit(Game* game, GameEnum gameName)
{
    setGameLevel(game,
                 gameName,
                 (gameName == GAMEEND_LOSER) ? GAMEINFO_ESC : GAMEINFO_PRESSKEY,
                 (gameName != GAMEEND_LOSER) ? &goToChooseLevelState_gamelogic :
                                               &noAction,
                 (gameName != GAMEEND_LOSER) ? &goToChooseLevelState_gamelogic :
                                               &noAction,
                 (gameName != GAMEEND_LOSER) ? &goToChooseLevelState_gamelogic :
                                               &noAction,
                 &goToChooseLevelState_gamelogic,
                 &noAction);
}

