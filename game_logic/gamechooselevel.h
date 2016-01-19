#pragma once
#include "gamelog.h"
#include "gamestate.h"
#include "gamechoosedificulty.h"

void gameChooseLevel_pressUp(Game* game)
{
    if(game->lowerLcdState == GAMELEVEL_PRO)
    {
        game->lowerLcdState = GAMELEVEL_CASUAL;
    }
}

void gameChooseLevel_pressDown(Game* game)
{
    if(game->lowerLcdState == GAMELEVEL_CASUAL)
    {
        game->lowerLcdState = GAMELEVEL_PRO;
    }
}

void gameChooseLevel_pressBack(Game* game)
{
    gameInit(game);
}

void gameChooseLevel_pressEnter(Game* game)
{
    game->level = game->lowerLcdState;
    gameChooseDificulty(game);
}

void gameChooseLevel(Game* game)
{
    game->upperLcdState = GAMEMENU_GAMELEVEL;
    game->lowerLcdState = GAMELEVEL_CASUAL;
    game->up = &gameChooseLevel_pressUp;
    game->down = &gameChooseLevel_pressDown;
    game->back = &gameChooseLevel_pressBack;
    game->enter = &gameChooseLevel_pressEnter;
}
