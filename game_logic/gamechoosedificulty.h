#pragma once
#include "gamesettings.h"
#include "gamechooselevel.h"

void gameChooseDificulty_pressEnter(Game* game)
{
    game->dificulty = game->lowerLcdState;
}

void gameChooseDificulty_pressBack(Game* game)
{
    gameChooseLevel(game);
}

void gameChooseDificulty_pressUp(Game* game)
{
    if(game->lowerLcdState != GAMEDIFICULTY_TURTLE)
    {
        --game->lowerLcdState;
    }
}

void gameChooseDificulty_pressDown(Game* game)
{
    if(game->lowerLcdState != GAMEDIFICULTY_ASIAN)
    {
        ++game->lowerLcdState;
    }
}

void gameChooseDificulty(Game* game)
{
    game->upperLcdState = GAMEMENU_GAMEDIFICULTY;
    game->lowerLcdState = GAMEDIFICULTY_NORMAL;
    game->up = &gameChooseDificulty_pressUp;
    game->down = &gameChooseDificulty_pressDown;
    game->back = &gameChooseDificulty_pressBack;
    game->enter = &gameChooseDificulty_pressEnter;
}
