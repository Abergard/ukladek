#pragma once
#include "gamelog.h"
#include "gamechoosedificulty.h"
#include "gamestate.h"
#include "game.h"

void left_gamelogic(Game* game)
{
}

void right_gamelogic(Game* game)
{
}

void choose_gamelogic(Game* game)
{
}

void pause_gamelogic(Game* game)
{
}

void update_gamelogic(Game* game)
{
}

void gameStartLevel(Game* game)
{
    setGameLevel(game,
                 GAMEMENU_GAMESTART,
                 GAMEMENU_GAMESTART,
                 &right_gamelogic,
                 &left_gamelogic,
                 &pause_gamelogic,
                 &choose_gamelogic,
                 &update_gamelogic);
}
