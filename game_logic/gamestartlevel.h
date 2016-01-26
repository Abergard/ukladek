#pragma once
#include <stdio.h>

typedef enum DIRECTION
{
    LEFT = -1,
    RIGHT = 1
}Direction;
void moveChar(Direction direction);
void left_gamelogic();
void right_gamelogic();
void pickCharAtCursor();
void dropCharAtCursor();
size_t findFirstNotEmptyCharInWord(const char* word);
void checkWord();
void choose_gamelogic();
void quit_gamelogic();
void update_gamelogic();
void prepareWords();
void initializeGame();
void gameStartLevel();
