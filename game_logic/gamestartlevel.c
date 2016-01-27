#include <string.h>
#include <stdlib.h>
#include "gamestartlevel.h"
#include "gamechooselevel.h"
#include "gamelog.h"
#include "game.h"
#include "gameinit.h"
#include "gamefunction.h"


void moveChar(Direction direction)
{
    if(game.isChosen)
    {
        changeCharAtPosition(game.word,
                             game.cursorPosition,
                             game.cursorPosition + direction);
    }
    changeCharAtPosition(game.wordWithChosenChar,
                         game.cursorPosition,
                         game.cursorPosition + direction);
    game.cursorPosition = game.cursorPosition + direction;
    game.needReDraw = 1;
}

void left_gamelogic()
{
    if(game.cursorPosition == 0)
    {
        return;
    }
    moveChar(LEFT);
}

void right_gamelogic()
{
    if(game.cursorPosition == strlen(getWord(game.wordId))-1)
    {
        return;
    }
    moveChar(RIGHT);
}

void pickCharAtCursor()
{
    game.wordWithChosenChar[game.cursorPosition] =
        game.word[game.cursorPosition];
    game.word[game.cursorPosition] = ' ';
    game.needReDraw = 1;
}

void dropCharAtCursor()
{
    game.word[game.cursorPosition] =
        game.wordWithChosenChar[game.cursorPosition];
    game.wordWithChosenChar[game.cursorPosition] = '*';
    game.needReDraw = 1;
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

void checkWord()
{
    const char* word = getWord(game.wordId);
    size_t i = findFirstNotEmptyCharInWord(game.word);
    if(i == MAX_STRING)
    {
        log("ERROR!\n");
        game.isEnd = 1;
        gameInit(GAMEEND_ERROR);
    }
    if(strncmp(&game.word[i], word, strlen(word)) == 0)
    {
        log("WIN\n");
        ++game.point;
        game.isEnd = 1;
        gameInit(GAMEEND_WIN);
    }
}

void choose_gamelogic()
{
    game.isChosen = !game.isChosen;
    if(game.isChosen)
    {
        pickCharAtCursor();
    }
    else
    {
        dropCharAtCursor();
        checkWord();
    }
}

void quit_gamelogic()
{
    gameChooseLevel();
}

void update_gamelogic()
{
    if( (game.level == GAMELEVEL_PRO) &&
        ((game.time - game.gameStartTimePoint) > getTimeDuration(game.dificulty))
      )
    {
        game.point = 0;
        game.isEnd = 1;
        gameInit(GAMEEND_LOSER);
    }
}

void prepareWords()
{
    game.wordId = rand() % 20;
    strncpy(game.wordWithChosenChar,
              game.emptyString,
              MAX_STRING);
    strncpy(game.word,
              game.emptyString,
              MAX_STRING);
    game.wordWithChosenChar[MAX_STRING] = '\0';
    game.word[MAX_STRING] = '\0';
    game.cursorPosition = 0;
    game.wordWithChosenChar[0] = '*';
    game.isChosen = 0;
    mixCharInWord(getWord(game.wordId));
}

void initializeGame()
{
    game.gameStartTimePoint = game.time;
    prepareWords();
    setGameLevel(GAMEMENU_GAMESTART,
                 GAMEMENU_GAMESTART,
                 &left_gamelogic,
                 &right_gamelogic,
                 &choose_gamelogic,
                 &quit_gamelogic,
                 &update_gamelogic);
}

void gameStartLevel()
{
    if(game.gameStartTimePoint == 0)
    {
        log("srand\n");
        srand(game.time);
        game.point = 0;
    }
    initializeGame();
}
