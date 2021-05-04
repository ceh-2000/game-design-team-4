#pragma once
#ifndef MINIGAME_LOGIC_4
#define MINIGAME_LOGIC_4

#include "MinigameLogic.h"

class MinigameLogic_4 {
private:
    std::shared_ptr<Song> song;
    sf::Vector2f chefDim;
    sf::Vector2f chefPosition;
    float chefSpeed;
    sf::Vector2f velocity = sf::Vector2f(400.0f, 400.0f);
    std::vector<std::vector<float>> arrowKeys;
    std::vector<BeatBoxLogic> beatBoxes;
    std::vector<float> timings;
    int score = 0;
    int totalScore = 0;
    int totalScoreIter = 0;
    int boxIter = 0;
    std::string grade;

public:
    MinigameLogic_4(std::shared_ptr<Song> song);

    std::vector<BeatBoxLogic> &getBeatBoxes() { return beatBoxes; }

    void incrementBoxIter() { boxIter++; }

    void updateBeatBoxes(const float &deltaTime);

    void addTotalScore(int i) { totalScoreIter+=i; } 
    
    void setTotalScore(int s) { totalScore+=s; }

    void setScore(const int& input,const int &tapCheck);

    int &getScore() { return score; }

    sf::Vector2f getChefDim() { return chefDim; }

    void setChefDim(sf::Vector2f &dim) { chefDim = dim; }
    // void setChefDim(float& a, float& b) { chefDim = sf::Vector2f(a,b); }

    sf::Vector2f getChefPos() { return chefPosition; }

    void setChefPos(sf::Vector2f &pos) { chefPosition = pos; }

    void setChefDim(float &a, float &b) { chefPosition = sf::Vector2f(a, b); }

    float &getChefSpeed() { return chefSpeed; }

    void setChefSpeed(float s) { chefSpeed = s; }

    std::vector<std::vector<float>> getArrowKeys() { return arrowKeys; }

    std::string gradeMinigame();

    std::string getRank() { return grade;}
};

#endif
