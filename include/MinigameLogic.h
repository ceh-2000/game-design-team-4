#pragma once
#ifndef MINIGAME_LOGIC_H
#define MINIGAME_LOGIC_H

#include <memory>
#include "BeatBoxLogic.h"
#include "Song.h"
#include "MinigameLogic_1.h"
#include "MinigameLogic_2.h"
#include "MinigameLogic_3.h"
#include "MinigameLogic_4.h"

class MinigameLogic {
protected:
    std::shared_ptr<Song> song;

    // Variable to detect and respond to hits
    int tapNum = 0;
    int backgroundColor = 0;
    bool isHit = false;
    bool animate = false;
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

    int getBackgroundColor() { return backgroundColor; }

    void startGame() { song->playSong(); }

    float getElapsedTime() { return song->getSongTime(); }

    float determineNextTap(float songTime);

    float determinePrevTap(float songTime);

    int tapCheck();

    bool regionCheck();

    void updatePostHit(const float &deltaTime);

    void stopGame() { this->song->stopSong(); }
};

#endif
