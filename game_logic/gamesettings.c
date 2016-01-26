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
        "Reading",//19
        "Lutownica"//20
    };
    return words[index];
}

size_t getTimeDuration(GameEnum gameDifiulty)
{
    static size_t time[] =
    {
        2400, // TURTLE
        120, // BEGINER
        60,  // NORMAL
        10   // ASIAN
    };
    return time[gameDifiulty-GAMEDIFICULTY_TURTLE];
}
