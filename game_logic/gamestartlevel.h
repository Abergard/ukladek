#pragma once
#include <string.h>
#include "gamestate.h"
#include "gamelog.h"
#include "game.h"
#include "gamefunction.h"

typedef enum DIRECTION
{
    LEFT = -1,
    RIGHT = 1
}Direction;

void moveChar(Game* game, Direction direction)
{
    if(game->isChosen)
    {
        changeCharAtPosition(game->word,
                             game->cursorPosition,
                             game->cursorPosition + direction);
    }
    changeCharAtPosition(game->wordWithChosenChar,
                         game->cursorPosition,
                         game->cursorPosition + direction);
    game->cursorPosition = game->cursorPosition + direction;
}

void left_gamelogic(Game* game)
{
    if(game->cursorPosition == 0)
    {
        return;
    }
    moveChar(game, LEFT);
}

void right_gamelogic(Game* game)
{
    if(game->cursorPosition == MAX_STRING-1)
    {
        return;
    }
    moveChar(game, RIGHT);
}

void pickCharAtCursor(Game* game)
{
    game->wordWithChosenChar[game->cursorPosition] =
        game->word[game->cursorPosition];
    game->word[game->cursorPosition] = ' ';
}

void dropCharAtCursor(Game* game)
{
    game->word[game->cursorPosition] =
        game->wordWithChosenChar[game->cursorPosition];
    game->wordWithChosenChar[game->cursorPosition] = '*';
}

size_t findFirstNotEmptyCharInWord(const char* word)
{
    for(size_t i = 0; i < MAX_STRING; ++i)
    {
        if(word[i] != ' ' && word[i] != '\0')
        {
            return i;
        }
    }
    return MAX_STRING;
}

void checkWord(Game* game)
{
    const char* word = getWord(game->wordId);
    size_t i = findFirstNotEmptyCharInWord(game->word);
        log("'%s' vs '%s' [size: %d][%d]\n",
            &game->word[i],
            word,
            strlen(word)-1,
            strlen(word));
    if(i == MAX_STRING)
    {
        log("ERROR!\n");
        gameInit(game, GAMEEND_ERROR);
    }
    if(strncmp(&game->word[i], word, strlen(word)) == 0)
    {
        log("WIN\n");
        ++game->point;
        gameInit(game, GAMEEND_WIN);
    }
}

void choose_gamelogic(Game* game)
{
    game->isChosen = !game->isChosen;
    if(game->isChosen)
    {
        pickCharAtCursor(game);
    }
    else
    {
        dropCharAtCursor(game);
        checkWord(game);
    }
}

void quit_gamelogic(Game* game)
{
    gameChooseLevel(game);
}

void update_gamelogic(Game* game)
{
    if(game->level == GAMELEVEL_PRO &&
       (game->time - game->gameStartTimePoint) > getTimeDuration(game->dificulty))
    {
        gameInit(game, GAMEEND_LOSER);
    }
}

void prepareWords(Game* game)
{
    game->wordId = rand() % 20;
    strncpy(game->wordWithChosenChar, game->emptyString, MAX_STRING);
    strncpy(game->word, game->emptyString, MAX_STRING);
    game->wordWithChosenChar[MAX_STRING] = '\0';
    game->word[MAX_STRING] = '\0';
    game->cursorPosition = 0;
    game->wordWithChosenChar[0] = '*';
    mixCharInWord(game, getWord(game->wordId));
}

void initializeGame(Game* game)
{
    prepareWords(game);
    setGameLevel(game,
                 GAMEMENU_GAMESTART,
                 GAMEMENU_GAMESTART,
                 &left_gamelogic,
                 &right_gamelogic,
                 &choose_gamelogic,
                 &quit_gamelogic,
                 &update_gamelogic);
    game->gameStartTimePoint = game->time;
}

void gameStartLevel(Game* game)
{
    if(game->gameStartTimePoint == 0)
    {
        log("srand\n");
        srand(game->time);
        game->point = 0;
    }
    initializeGame(game);
}
