#pragma once
#include "gamelog.h"
#include "gamestate.h"

void gameInit_press(Game* game)
{
    gameChooseLevel(game);
}

void gameInit(Game* game)
{
    game->state = GAMESTATE_MENU;
    game->upperLcdState = GAMEMENU_GAMENAME;
    game->lowerLcdState = GAMEINFO_PRESSKEY;
    game->up = &gameInit_press;
    game->down = &gameInit_press;
    game->enter = &gameInit_press;
    game->back = &gameInit_press;
}
