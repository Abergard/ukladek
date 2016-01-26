#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG

#ifdef DEBUG
#include "gamelog.h"
#endif
#include "gamesettings.h"
#include "game.h"
#include "gameinit.h"

void display()
{
    log("----------------\n");
    log("1)%s(1\n", getFirstLineToDisplay());
    log("2)%s(2\n", getSecondLineToDisplay());
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
          game.up();
          return;
      case 's':
          game.back();
          return;
      case 'd':
          game.enter();
          return;
      case 'f':
          game.down();
          return;
      case 'p':
          log("'%s' vs '%s'\n", game.word, getWord(game.wordId));
          return;
    };
}

int main()
{
    log("%u", strlen(getWord(1)));
    gameInit(GAMEMENU_GAMENAME);
    while(1)
    {
        display();
        readKeyboard();
        updateGame();
    }
    return 0;
}
