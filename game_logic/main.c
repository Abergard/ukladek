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
    .enter = &noAction,
    .word = "                "
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

#include "gamesettings.h"

#define true 1
#define false 0

int changeRandomlyCharPosition(size_t randPosition,
                               size_t pos,
                               const char* word)
{
    log("%u vs %u\n",pos, randPosition);
    log("change ");
    log("%c", game.word[randPosition]);
    log(" vs ");
    log("%c", word[randPosition]);
    log(" vs ");
    log("%c", word[pos]);
    log("\n");
    if(game.word[randPosition] == ' ' &&
       (pos > 0 || word[randPosition] != word[pos]))
    {
        log("found\n");
        return true;
    }
    else
    {
        log("not found\n");
        return false;
    }
}

int main()
{
    srand((unsigned) time(NULL));
    const char* word = getWord(1);
    size_t len = strlen(word);
    size_t randPosition;
    int isChange = false;
    size_t retryNumber = 0;
    for(size_t pos = 0; pos < len; ++pos)
    {
        randPosition = (rand() % len);
        retryNumber = 0;
        log("%u vs %u\n",pos, randPosition);
        while(retryNumber < len &&
              changeRandomlyCharPosition(randPosition, pos, word) == false)
        {
            randPosition = (randPosition + 1) % len;
            ++retryNumber;
        }
        game.word[randPosition] = word[pos];
        log("put %c in pos %u from pos %u\n", word[pos], randPosition, pos);
    }
    log(word);
    log("\n");
    log(game.word)
    /* log("%u", strlen(getWord(1))); */
    /* gameInit(&game); */
    /* while(1) */
    /* { */
    /*     display(); */
    /*     readKeyboard(); */
    /* } */
    return 0;
}
