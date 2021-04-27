#pragma once
#ifndef MINIGAME_LOGIC_3
#define MINIGAME_LOGIC_3

#include "MinigameLogic.h"

class MinigameLogic_3 {
private:
    std::shared_ptr<Song> song;
    sf::Vector2f ingredientDim;
    sf::Vector2f position;
    int score = 0;

    float ingredientSpeed;
    std::vector<float> trueCuts;
    std::vector<float> playerCuts;

    std::vector<BeatBoxLogic> beatBoxes;

    sf::Vector2f knifePos;
    float knifeSpeed = 2500;

public:
    MinigameLogic_3(std::shared_ptr<Song> song);

    void move(const float &dt);

    int getScore() { return score; }

    std::vector<BeatBoxLogic> getBeatBoxes() { return beatBoxes; }

    sf::Vector2f getIngredientDim() { return ingredientDim; }

    void setIngreientDim(sf::Vector2f &dim) { ingredientDim = dim; }

    void setIngredientDim(float &a, float &b) { ingredientDim = sf::Vector2f(a, b); }

    sf::Vector2f getChefPos() { return position; }

    void setChefPos(sf::Vector2f &pos) { position = pos; }

    float getIngredientSpeed() { return ingredientSpeed; }

    void setIngredientSpeed(float s) { ingredientSpeed = s; }

    sf::Vector2f getKnifePos() { return knifePos; }

    float getKnifeSpeed() { return knifeSpeed; }

    void setKnifePos(sf::Vector2f &pos) { this->knifePos = pos; }

    std::vector<float> getTrueCuts() { return trueCuts; }

    std::vector<float> getPlayerCuts() { return playerCuts; }

    void moveKnife(const float &dt);

    void update(const float &dt);

    void splitBox();

    void updateBeatBoxes(const float &deltaTime);


};

#endif