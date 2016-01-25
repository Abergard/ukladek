#pragma once
#include "gamelog.h"
#include "gamechoosedificulty.h"
#include "gamestate.h"
#include "game.h"

void showNextLevel_gamelogic(Game* game)
{
    if(isGameActionEqual(game, GAMELEVEL_PRO))
    {
        setGameAction(game, GAMELEVEL_CASUAL);
    }
}

void showPreviousLevel_gamelogic(Game* game)
{
    if(isGameActionEqual(game, GAMELEVEL_CASUAL))
    {
        setGameAction(game, GAMELEVEL_PRO);
    }
}

void setLevelAndGoToNextState_gamelogic(Game* game)
{
    saveActionStateAsLevel(game);
    if(isGameLevelEqual(game, GAMELEVEL_CASUAL))
    {
        log("1");
        gameStartLevel(game);
    }
    else
    {
        log("2");
        gameChooseDificulty(game);
    }
}

void gameChooseLevel(Game* game)
{
    setGameLevel(game,
                 GAMEMENU_GAMELEVEL,
                 GAMELEVEL_CASUAL,
                 &showNextLevel_gamelogic,
                 &showPreviousLevel_gamelogic,
                 &setLevelAndGoToNextState_gamelogic,
                 &noAction,
                 &noAction);
}
