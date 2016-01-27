#include <stdlib.h>
#include "gameinit.h"
#include "gamechooselevel.h"
#include "gamestartlevel.h"

void goToChooseLevelState_gamelogic()
{
    if(game.menuState == GAMEEND_WIN)
    {
        gameStartLevel();
    }
    else
    {
        gameChooseLevel();
    }
}

void gameInit(GameEnum gameName)
{
    setGameLevel(gameName,
                 (gameName == GAMEEND_LOSER) ? GAMEINFO_ESC : GAMEINFO_PRESSKEY,
                 (gameName != GAMEEND_LOSER) ? &goToChooseLevelState_gamelogic : &noAction,
                 (gameName != GAMEEND_LOSER) ? &goToChooseLevelState_gamelogic : &noAction,
                 (gameName != GAMEEND_LOSER) ? &goToChooseLevelState_gamelogic : &noAction,
                 &goToChooseLevelState_gamelogic,
                 &noAction);
}
