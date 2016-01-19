#pragma once
#include "gamesettings.h"

typedef struct Game
{
    void (*up)(struct Game*);
    void (*down)(struct Game*);
    void (*enter)(struct Game*);
    void (*back)(struct Game*);
    GameEnum upperLcdState;
    GameEnum lowerLcdState;
    GameEnum level;
    GameEnum dificulty;
    GameEnum state;
    char word[16];
}Game;
