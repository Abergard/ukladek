#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define DEBUG

#ifdef DEBUG
#include "gamelog.h"
#endif

#include "game.h"
#include "gameinit.h"

void noAction(Game* game)
{
}

static Game game =
{
    /* .type = GAMETYPE_CASUAL, */
    /* .dificulty = GAMEDIFICULTY_NORMAL, */
    /* .lcd.firstLine =  "   Words King  ", */
    /* .lcd.secondLine = "<< Press Key >>", */
    /* .gameWords = */
    /* { */
    /*     "alamakota", */
    /*     "jadedobabci", */
    /*     "olek" */
    /* } */
    .up = &noAction,
    .down = &noAction,
    .back = &noAction,
    .enter = &noAction
};

void display()
{
    log("----------------\n");
    log("%s\n", toString(game.upperLcdState));
    log("%s\n", toString(game.lowerLcdState));
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
    gameInit(&game);
    while(1)
    {
        display();
        readKeyboard();
    }
    return 0;
}
