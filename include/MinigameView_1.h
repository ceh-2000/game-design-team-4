#pragma once
#ifndef MINIGAME_VIEW_1
#define MINIGAME_VIEW_1

#include "MinigameView.h"
#include "MinigameLogic_1.h"

class MinigameView_1 {
private:
    std::shared_ptr<MinigameLogic_1> miniLogic;
    std::shared_ptr<sf::RenderWindow> app;
    sf::Sprite bowl;
    sf::Sprite ingredient;

    //sf::CircleShape circle = sf::CircleShape(5.0f);

public:
    MinigameView_1(std::shared_ptr<MinigameLogic_1> MinigameLogic_1, std::shared_ptr<sf::RenderWindow> app);

    void updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes);

    void draw();

    void update(const float &deltaTime);
};

#endif
