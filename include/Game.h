#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include "Song.h"
#include "BeatBoxLogic.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Game
{
protected:
    int score = 0;
    int difficult = 1;
    int currentGame = 1;
    bool isActive = true;
    // Pointer to whatever the current game is

public:
    // Something to start and stop current game idk fam
    Game();
};
#endif

