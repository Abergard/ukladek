#include "gamesettings.h"

const char* toString(GameEnum gameEnum)
{
    static char* names[] =
    {//  123456789.......
        "                ",//0
        "     Casual     ",
        "   Time Limit   ",

        "  Ukladek Game1 ",//3
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
        "Tom",//1
        "Luke",//2
        "Banan",//3
        "Mikro",//4
        "AVR",//5
        "Laptop",//6
        "Porojekt",//7
        "Ster",//8
        "Gram",//9
        "Atmega",//10
        "Wlam",//11
        "Procesor",//12
        "Obudowa",//13
        "Korek",//14
        "Ogorek",//15
        "Abelard",//16
        "Kran",//17
        "Komin",//18
        "Read",//19
        "Lucek"//20
    };
    return words[index];
}

size_t getTimeDuration(GameEnum gameDifiulty)
{
    static size_t time[] =
    {
        2403, // TURTLE
        123, // BEGINER
        63,  // NORMAL
        13   // ASIAN
    };
    return time[gameDifiulty-GAMEDIFICULTY_TURTLE];
}
