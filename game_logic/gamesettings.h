#pragma once

typedef enum GameEnum
{
    GAMELEVEL_CASUAL = 0,
    GAMELEVEL_PRO = 1,

    GAMEMENU_GAMENAME = 2,
    GAMEMENU_GAMELEVEL = 3,
    GAMEMENU_GAMEDIFICULTY = 4,

    GAMEINFO_PRESSKEY = 5,
    GAMEINFO_WIN = 6,
    GAMEINFO_LOSE = 7,

    GAMEDIFICULTY_TURTLE = 8,
    GAMEDIFICULTY_BEGINNER = 9,
    GAMEDIFICULTY_NORMAL = 10,
    GAMEDIFICULTY_ASIAN = 11,

    GAMESTATE_MENU = 12,
    GAMESTATE_GAME = 13,
    GAMESTATE_PAUSE = 14
}GameEnum;

const char* toString(GameEnum gameEnum)
{
    static char* names[] =
    {//  123456789.......
        "     Casual     ",//0
        "   Time Limit   ",//1

        "  Ukladek Game  ",//2
        "  Choose Level  ",//3
        "    Dificulty   ",//4

        "  <<  Press >>  ",//5
        "       Win      ",//6
        "       Lose     ",//7

        "      Turtle    ",//8
        "     Beginner   ",//9
        "      Normal    ",//10
        "      Asian     " //11
    };
    return names[gameEnum];
}
