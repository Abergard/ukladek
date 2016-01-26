#include <string.h>
#include <stdlib.h>
#include "gamefunction.h"
#include "game.h"

int changeRandomlyCharPosition(size_t randPosition,
                               size_t pos,
                               const char* word)
{
    if(game.word[randPosition] == ' ' &&
       (pos > 0 || word[randPosition] != word[pos]))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void mixCharInWord(const char* word)
{
    size_t len = strlen(word);
    size_t randPosition;
    size_t retryNumber = 0;
    for(size_t pos = 0; pos < len; ++pos)
    {
        randPosition = (rand() % len);
        retryNumber = 0;
        while(retryNumber < len &&
              changeRandomlyCharPosition(randPosition, pos, word) == 0)
        {
            randPosition = (randPosition + 1) % len;
            ++retryNumber;
        }
        game.word[randPosition] = word[pos];
    }
}

void changeCharAtPosition(char* word, size_t posFirst, size_t posSecond)
{
    char tmp = word[posFirst];
    word[posFirst] = word[posSecond];
    word[posSecond] = tmp;
}
