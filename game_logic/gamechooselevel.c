#include "gamechooselevel.h"
#include "gamelog.h"
#include "gamechoosedificulty.h"
#include "gamestartlevel.h"
#include "game.h"

void showNextLevel_gamelogic()
{
    if(isGameActionEqual(GAMELEVEL_PRO))
    {
        setGameAction(GAMELEVEL_CASUAL);
    }
}

void showPreviousLevel_gamelogic()
{
    if(isGameActionEqual(GAMELEVEL_CASUAL))
    {
        setGameAction(GAMELEVEL_PRO);
    }
}

void setLevelAndGoToNextState_gamelogic()
{
    saveActionStateAsLevel();
    if(isGameLevelEqual(GAMELEVEL_CASUAL))
    {
        gameStartLevel();
    }
    else
    {
        gameChooseDificulty();
    }
}

void gameChooseLevel()
{
    setGameLevel(GAMEMENU_GAMELEVEL,
                 GAMELEVEL_CASUAL,
                 &showNextLevel_gamelogic,
                 &showPreviousLevel_gamelogic,
                 &setLevelAndGoToNextState_gamelogic,
                 &noAction,
                 &noAction);
}
