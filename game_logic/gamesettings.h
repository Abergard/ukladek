#pragma once

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

const char* toString(GameEnum gameEnum)
{
    static char* names[] =
    {//  123456789.......
        "                ",//0
        "     Casual     ",
        "   Time Limit   ",

        "  Ukladek Game  ",//3
        "  Choose Level  ",
        "    Dificulty   ",

        "  <<  Press >>  ",//6
        "  <<   ESC  >>  ",
        "       Win      ",
        "       Lose     ",

        "      Turtle    ",//9
        "     Beginner   ",
        "      Normal    ",
        "      Asian     ",

        "       WIN      ",//13
        "      LOSER     ",
        "      ERROR     "
    };
    return names[gameEnum];
}

const char* getWord(size_t index)
{
    static char* words[] =
    {//  123456789.......
        "Tomek",//1
        "Lukasz",//2
        "Banan",//3
        "Mikrokontroler",//4
        "Plyta AVR",//5
        "Laptop",//6
        "Projektowanie",//7
        "Sterowanie",//8
        "Programowanie",//9
        "Atmega",//10
        "Bezpieczenstwo",//11
        "Procesor",//12
        "Obudowa",//13
        "Konfucjusz",//14
        "Indiosynkrazja",//15
        "Abelard",//16
        "Katarzyna",//17
        "Komentarz",//18
        "Reading"//19
    };
    return words[index];
}

size_t getTimeDuration(GameEnum gameDifiulty)
{
    static size_t time[] =
    {
        240, // TURTLE
        120, // BEGINER
        60,  // NORMAL
        10   // ASIAN
    };
    log("timer: %d", time[gameDifiulty-GAMEDIFICULTY_TURTLE]);
    return time[gameDifiulty-GAMEDIFICULTY_TURTLE];
}
