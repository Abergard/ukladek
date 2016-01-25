#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG

#ifdef DEBUG
#include "gamelog.h"
#endif

#include "game.h"
#include "gameinit.h"

static Game game =
{
    .up = &noAction,
    .down = &noAction,
    .back = &noAction,
    .enter = &noAction,
    .updateState = &noAction,
    .isChosen = 0,
    .needReDraw = 0,
    .time = 0,
    .gameStartTimePoint = 0,
    .cursorPosition = 0,
    .emptyString = "                "
};

void display()
{
    log("----------------\n");
    log("1)%s(1\n", getFirstLineToDisplay(&game));
    log("2)%s(2\n", getSecondLineToDisplay(&game));
    log("----------------\n");
}

void readKeyboard()
{
    char key = getch();
    log("%c\n", key);
    switch(key)
    {
      case 'q':
          exit(0);
      case 'a':
          game.up(&game);
          return;
      case 's':
          game.back(&game);
          return;
      case 'd':
          game.enter(&game);
          return;
      case 'f':
          game.down(&game);
          return;
      case 'p':
          log("'%s' vs '%s'\n", game.word, getWord(game.wordId));
          return;
    };
}



int main()
{
    log("%u", strlen(getWord(1)));
    gameInit(&game, GAMEMENU_GAMENAME);
    while(1)
    {
        display();
        readKeyboard();
        updateGame(&game);
    }
    return 0;
}
