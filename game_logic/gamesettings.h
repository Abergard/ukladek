#pragma once
#include <stdio.h>

typedef enum GameEnum
{

    GAMEMENU_GAMESTART = 0,

    GAMELEVEL_CASUAL = 1,
    GAMELEVEL_PRO = 2,

    GAMEMENU_GAMENAME = 3,
    GAMEMENU_GAMELEVEL = 4,
    GAMEMENU_GAMEDIFICULTY = 5,

    GAMEINFO_PRESSKEY = 6,
    GAMEINFO_ESC = 7,
    GAMEINFO_WIN = 8,
    GAMEINFO_LOSE = 9,

    GAMEDIFICULTY_TURTLE = 10,
    GAMEDIFICULTY_BEGINNER = 11,
    GAMEDIFICULTY_NORMAL = 12,
    GAMEDIFICULTY_ASIAN = 13,

    GAMEEND_WIN = 14,
    GAMEEND_LOSER = 15,
    GAMEEND_ERROR = 16
}GameEnum;

#define MAX_STRING 16

const char* toString(GameEnum gameEnum);
const char* getWord(size_t index);
size_t getTimeDuration(GameEnum gameDifiulty);
