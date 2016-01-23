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
    .needReDraw = 0,
    .time = 0,
    .cursorPosition = 0,
    .wordWithChoosenChar = "                ",
    .word = "                "
};

void display()
{
    log("----------------\n");
    log("%s\n", getFirstLineToDisplay(&game));
    log("%s\n", getSecondLineToDisplay(&game));
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
    };
}



int main()
{
    log("%u", strlen(getWord(1)));
    gameInit(&game);
    while(1)
    {
        display();
        readKeyboard();
        updateGame(&game);
    }
    return 0;
}
