#pragma once
#ifndef MINIGAME_VIEW_1
#define MINIGAME_VIEW_1

#include "MinigameView.h"
#include "MinigameLogic_1.h"
#include<string>

class MinigameView_1 {
private:
    std::shared_ptr<MinigameLogic_1> miniLogic;
    std::shared_ptr<sf::RenderWindow> app;

    sf::Texture texture;
    sf::Font font;
    sf::IntRect rectSourceSprite;
    sf::Text scoreText;

    sf::CircleShape circle = sf::CircleShape(100.0f);
public:
    MinigameView_1(std::shared_ptr<MinigameLogic_1> MinigameLogic_1, std::shared_ptr<sf::RenderWindow> app);

    void drawBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes);

    void drawBowl();

    void drawStatic();

    void update(const float &deltaTime);

    void drawScore(int score);
};

#endif