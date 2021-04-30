#pragma once
#ifndef MINIGAME_VIEW_2
#define MINIGAME_VIEW_2
#include "MinigameView.h"
#include "MinigameLogic_2.h"
class MinigameView_2
{
private:
    std::shared_ptr<sf::RenderWindow> app;
    std::shared_ptr<MinigameLogic_2> miniLogic;

    //Test Shapes
    sf::CircleShape cPizza;
    sf::Texture pizzaTexture;
    sf::RectangleShape baseCut;//model cut object to transform
    sf::RectangleShape knifeBox;

    std::vector<sf::RectangleShape> actualCuts;
    std::vector<sf::RectangleShape> playerCuts;

    sf::Font font;

    bool moveKnife = false;

public:
    MinigameView_2(std::shared_ptr<MinigameLogic_2> MinigameLogic_2, std::shared_ptr<sf::RenderWindow> app);
    void drawPlay();
    void drawEndGame();
    void update(const float& deltaTime);
    void cutPizza() { moveKnife = true; }
};

#endif
