#pragma once
#include <stdio.h>
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
    short isChosen;
    short needReDraw;
    size_t point;
    unsigned time;
    unsigned gameStartTimePoint;
    short cursorPosition;
    size_t wordId;
    const char* emptyString;
    char wordWithChosenChar[MAX_STRING+1];
    char word[MAX_STRING+1];
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
    game->needReDraw = 1;
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

short isGameWin(Game* game)
{
    return game->menuState == GAMEEND_WIN;
}

void nextGameAction(Game* game)
{
    ++game->actionState;
    game->needReDraw = 1;
}

void previousGameAction(Game* game)
{
    --game->actionState;
    game->needReDraw = 1;
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
        return game->wordWithChosenChar;
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
    else if(isGameWin(game))
    {
        static char str[16];
        sprintf(str, "p:%d", game->point);
        return str;
    }
    else
    {
        return toString(game->actionState);
    }
}

unsigned getGameTime(Game* game)
{
	if(isGameRunning(game))
	{
	    return game->time - game->gameStartTimePoint;
	}
	else
	{
		return 0;
	}
}

void updateGame(Game* game)
{
    game->time = game->time + 1;
    game->updateState(game);
}
