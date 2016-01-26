#pragma once
#include "gamesettings.h"

void gameInit(Game* game, GameEnum gameEnum);
void gameChooseLevel(Game* game);
void gameChooseDificulty(Game* game);
void gameStartLevel(Game* game);

#include "gameinit.h"
#include "gamechooselevel.h"
#include "gamechoosedificulty.h"
#include "gamestartlevel.h"

