#pragma once
#ifndef MINIGAME_LOGIC_1
#define MINIGAME_LOGIC_1

#include "MinigameLogic.h"

class MinigameLogic_1 {
private:
    // General variables
    std::shared_ptr<Song> song;
    sf::Vector2f windowSize;
    int score = 0;
    int goodTapBoost = 300;
    int almostTapBoost = 150;
    int badTapBoost = -50;

    // Dropping ingredients variables
    sf::Vector2f ingredientDim = sf::Vector2f(50.0f, 50.0f);
    float ingredientSpeed = 500.0f;
    std::vector<BeatBoxLogic> beatBoxes;
    std::vector<bool> isGoodVector;
    float curBeatBoxIndex = 0;

    // Bowl variables
    float distanceToBowl;
    sf::Vector2f bowlSize = sf::Vector2f(200.0f, 100.0f);
    sf::Vector2f bowlPosition;
    sf::Vector2f bowlStartPosition;
    float bowlSpeed = 1000.0f;
    bool bowlMovingOut = true;
    int moveBowl = 0;
    float maxAmountToMoveBowl = 0;


public:
    MinigameLogic_1(std::shared_ptr<Song> song, float x, float y);

    std::vector<BeatBoxLogic> getBeatBoxes() { return beatBoxes; }

    std::vector<bool> getIsGoodVector() { return isGoodVector; }

    int getScore() { return score; }

    sf::Vector2f getBowlSize() { return bowlSize; }

    sf::Vector2f getBowlPosition() { return bowlPosition; }

    sf::Vector2f getIngredDim() { return ingredientDim; }

    void updateBeatBoxes(const float &deltaTime);

    void updateBowl(const float &deltaTime);

    void reactTap(const int &hitOutcome, const bool &isRightTap);

    void noTap(const bool &didHit);

    void update(const float &deltaTime, const bool &didHit);

};

#endif