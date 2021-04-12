#pragma once
#ifndef MINIGAME_LOGIC_H
#define MINIGAME_LOGIC_H
#include "Game.h"
class MinigameLogic : std::enable_shared_from_this<MinigameLogic>
{
protected:
    // General variables for game
    std::shared_ptr<Song> song;

    // Variables for before a hit occurs
    std::vector<BeatBoxLogic> beatBoxes;

    // Variable to detect and respond to hits
    int tapNum = 0;
    int backgroundColor = 0;
    bool isHit = false;
    bool animate;
    int counter = 0;
    bool resetHitYet = false;

    // Act and success regions (TODO: vary between songs?)
    float actRegion = 0.45f;   //defines entire hit action region for a given song
    float winRegion = 0.15f;   //defines successful hit time window in action region
    float almostRegion = 0.3f; //defines near hit / near miss time window in action region

    // Variables for timings
    float elapsedDuration;
    float duration = 0.075f;
public:
    MinigameLogic(std::shared_ptr<Song> song);

    float determineNextTap(float songTime);
    float determinePrevTap(float songTime);

    void tapCheck();
    void regionCheck();
    void updateBeatBoxes(const float& deltaTime);
    void update(const float& deltaTime);

    // Consider removing this?
    virtual void move(const float& dt) = 0;
};
#endif