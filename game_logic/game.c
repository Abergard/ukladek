#include <stdio.h>
#include "game.h"
#include "gamesettings.h"

void noAction()
{
}

Game game =
{
    .up = &noAction,
    .down = &noAction,
    .back = &noAction,
    .enter = &noAction,
    .updateState = &noAction,
    .isChosen = 0,
    .needReDraw = 0,
    .time = 0,
    .gameStartTimePoint = 0,
    .cursorPosition = 0,
    .emptyString = "                "
};

void setGameLevel(GameEnum menuState,
                  GameEnum actionState,
                  GameFunction upAction,
                  GameFunction downAction,
                  GameFunction enterAction,
                  GameFunction backAction,
                  GameFunction updateAction)
{
    game.menuState = menuState;
    game.actionState = actionState;
    game.up = upAction;
    game.down = downAction;
    game.back = backAction;
    game.enter = enterAction;
    game.updateState = updateAction;
    game.needReDraw = 1;
}

void setGameAction(GameEnum action)
{
    game.actionState = action;
    game.needReDraw = 1;
}

short isGameActionEqual(GameEnum action)
{
    return game.actionState == action;
}

short isGameLevelEqual(GameEnum level)
{
    return game.level == level;
}

short isGameRunning()
{
    return game.menuState == GAMEMENU_GAMESTART;
}

short isGameWin()
{
    return game.menuState == GAMEEND_WIN;
}

void nextGameAction()
{
    ++game.actionState;
    game.needReDraw = 1;
}

void previousGameAction()
{
    --game.actionState;
    game.needReDraw = 1;
}

void saveActionStateAsLevel()
{
    game.level = game.actionState;
}

void saveActionStateAsDificulty()
{
    game.dificulty = game.actionState;
}

const char* getFirstLineToDisplay()
{
    if(isGameRunning())
    {
        return game.wordWithChosenChar;
    }
    else
    {
        return toString(game.menuState);
    }
}

const char* getSecondLineToDisplay()
{
    if(isGameRunning())
    {
        return game.word;
    }
    else if(isGameWin())
    {
        static char str[16];
        sprintf(str, "p:%d", game.point);
        return str;
    }
    else
    {
        return toString(game.actionState);
    }
}

unsigned getGameTime()
{
    if(isGameRunning(game) == 0)
    {
        return 0;
    }

    unsigned time = game.time - game.gameStartTimePoint;
    if(game.level == GAMELEVEL_CASUAL)
    {
        return time;
    }

    return getTimeDuration(game.dificulty) - time;
}

void updateGame()
{
    game.time = game.time + 1;
    game.updateState();
}
