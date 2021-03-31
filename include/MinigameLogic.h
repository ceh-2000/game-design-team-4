#pragma once
#ifndef MINIGAME_LOGIC_H
#define MINIGAME_LOGIC_H
#include "Game.h"
class MinigameLogic : std::enable_shared_from_this<MinigameLogic>
{
private:
    int currentGame;
    std::shared_ptr<Song> song;
    std::vector<float> userTimings;
    int score;
    int correctTimingPos;
    int difficult;
public:
    MinigameLogic(/* args */);
    int determineHitAccuracy();
    std::vector<float> computerNextInt(float& time);
    virtual void move(const float& dt) = 0;
};
#endif