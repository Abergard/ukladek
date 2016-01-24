#pragma once
#include "gamesettings.h"

typedef struct Game
{
    void (*up)(struct Game*);
    void (*down)(struct Game*);
    void (*enter)(struct Game*);
    void (*back)(struct Game*);
    void (*updateState)(struct Game*);
    GameEnum menuState;
    GameEnum actionState;
    GameEnum level;
    GameEnum dificulty;
    short needReDraw;
    short time;
    short gameStartTimePoint;
    short cursorPosition;
    char* wordWithChoosenChar;
    char* word;
    char* wordId;
}Game;

typedef void(*GameFunction)(struct Game*);

void noAction(Game* game){}
void setGameLevel(Game* game,
                  GameEnum menuState,
                  GameEnum actionState,
                  GameFunction upAction,
                  GameFunction downAction,
                  GameFunction enterAction,
                  GameFunction backAction,
                  GameFunction updateAction)
{
    game->menuState = menuState;
    game->actionState = actionState;
    game->up = upAction;
    game->down = downAction;
    game->back = backAction;
    game->enter = enterAction;
    game->updateState = updateAction;
    game->needReDraw = 1;
}

void setGameAction(Game* game,
                   GameEnum action)
{
    game->actionState = action;
}

short isGameActionEqual(Game* game,
                        GameEnum action)
{
    return game->actionState == action;
}

short isGameLevelEqual(Game* game,
                       GameEnum level)
{
    return game->level == level;
}

short isGameRunning(Game* game)
{
    return game->menuState == GAMEMENU_GAMESTART;
}

void nextGameAction(Game* game)
{
    ++game->actionState;
}

void previousGameAction(Game* game)
{
    --game->actionState;
}

void saveActionStateAsLevel(Game* game)
{
    game->level = game->actionState;
}

void saveActionStateAsDificulty(Game* game)
{
    game->dificulty = game->actionState;
}

const char* getFirstLineToDisplay(Game* game)
{
    if(isGameRunning(game))
    {
        return game->wordWithChoosenChar;
    }
    else
    {
        return toString(game->menuState);
    }
}

const char* getSecondLineToDisplay(Game* game)
{
    if(isGameRunning(game))
    {
        return game->word;
    }
    else
    {
        return toString(game->actionState);
    }
}

short getGameTimer(Game* game)
{
    return game->time;
}

void updateGame(Game* game)
{
    ++game->time;
    game->updateState(game);
}
