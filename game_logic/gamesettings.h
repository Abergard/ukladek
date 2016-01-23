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
    GAMEINFO_WIN = 7,
    GAMEINFO_LOSE = 8,

    GAMEDIFICULTY_TURTLE = 9,
    GAMEDIFICULTY_BEGINNER = 10,
    GAMEDIFICULTY_NORMAL = 11,
    GAMEDIFICULTY_ASIAN = 12,

    GAMESTATE_MENU = 13, //TODO: delete it
    GAMESTATE_GAME = 14,
    GAMESTATE_PAUSE = 15
}GameEnum;

const char* toString(GameEnum gameEnum)
{
    static char* names[] =
    {//  123456789.......
        "                ",//0
        "     Casual     ",//1
        "   Time Limit   ",//2

        "  Ukladek Game  ",//3
        "  Choose Level  ",//4
        "    Dificulty   ",//5

        "  <<  Press >>  ",//6
        "       Win      ",//7
        "       Lose     ",//8

        "      Turtle    ",//9
        "     Beginner   ",//10
        "      Normal    ",//11
        "      Asian     " //12
    };
    return names[gameEnum];
}

const char* getWord(size_t index)
{
    static char* words[] =
    {//  123456789.......
        "Tomek",//1
        "Lukasz",//2
        "Banan"//3
        "Mikrokontroler",//4
        "Plyta AVR",//5
        "Laptop",//6
        "Projektowanie",//7
        "Sterowanie",//8
        "Programowanie",//9
        "Atmega",//10
        "Bezpieczenstwo",//11
        "Procesor"//12
        "Obudowa"//13
        "Konfucjusz"//14
        "Indiosynkrazja"//15
        "Abelard"//16
        "Katarzyna"//17
        "Komentarz"//18
        "Reading"//19
    };
    return words[index];
}
