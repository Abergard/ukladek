#pragma once
#include "gamesettings.h"

typedef void(*GameFunction)();
typedef struct Game
{
    GameFunction up;
    GameFunction down;
    GameFunction enter;
    GameFunction back;
    GameFunction updateState;
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

extern Game game;

void noAction();
void setGameLevel(GameEnum menuState,
                  GameEnum actionState,
                  GameFunction upAction,
                  GameFunction downAction,
                  GameFunction enterAction,
                  GameFunction backAction,
                  GameFunction updateAction);

void setGameAction(GameEnum action);
short isGameActionEqual(GameEnum action);
short isGameLevelEqual(GameEnum level);
short isGameRunning();
short isGameWin();
void nextGameAction();
void previousGameAction();
void saveActionStateAsLevel();
void saveActionStateAsDificulty();
const char* getFirstLineToDisplay();
const char* getSecondLineToDisplay();
unsigned getGameTime();
void updateGame();
