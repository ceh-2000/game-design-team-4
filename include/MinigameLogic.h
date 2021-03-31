#pragma once
#ifndef MINIGAME_LOGIC_H
#define MINIGAME_LOGIC_H
#include "Game.h"
class MinigameLogic : std::enable_shared_from_this<MinigameLogic>
{
private:
    
public:
    MinigameLogic(/* args */);
    virtual void move(const float& dt) = 0;
};
#endif