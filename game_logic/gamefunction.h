#pragma once
#include "game.h"

int changeRandomlyCharPosition(size_t randPosition,
                               size_t pos,
                               const char* word,
                               Game* game)
{
    if(game->word[randPosition] == ' ' &&
       (pos > 0 || word[randPosition] != word[pos]))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void mixCharInWord(const char* word, Game* game)
{
    size_t len = strlen(word);
    size_t randPosition;
    int isChange = 0;
    size_t retryNumber = 0;
    for(size_t pos = 0; pos < len; ++pos)
    {
        randPosition = (rand() % len);
        retryNumber = 0;
        while(retryNumber < len &&
              changeRandomlyCharPosition(randPosition, pos, word, game) == 0)
        {
            randPosition = (randPosition + 1) % len;
            ++retryNumber;
        }
        game->word[randPosition] = word[pos];
    }
}
