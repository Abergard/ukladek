#pragma once
#include "gamesettings.h"
#include "gamechooselevel.h"
#include "gamestate.h"
#include "game.h"

void setDificultyAndGoToTheNextLevel_gamelogic(Game* game)
{
    saveActionStateAsDificulty(game);
    gameStartLevel(game);
}

void backToPreviousLevel_gamelogic(Game* game)
{
    gameChooseLevel(game);
}

void showPreviousDificulty_gamelogic(Game* game)
{
    if(!isGameActionEqual(game, GAMEDIFICULTY_TURTLE))
    {
        previousGameAction(game);
    }
}

void showNextDificulty_gamelogic(Game* game)
{
    if(!isGameActionEqual(game, GAMEDIFICULTY_ASIAN))
    {
        nextGameAction(game);
    }
}


void gameChooseDificulty(Game* game)
{
    setGameLevel(game,
                 GAMEMENU_GAMEDIFICULTY,
                 GAMEDIFICULTY_NORMAL,
                 &showPreviousDificulty_gamelogic,
                 &showNextDificulty_gamelogic,
                 &setDificultyAndGoToTheNextLevel_gamelogic,
                 &backToPreviousLevel_gamelogic,
                 &noAction);
}
