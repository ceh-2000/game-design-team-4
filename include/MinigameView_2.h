#pragma once
#ifndef MINIGAME_VIEW_2
#define MINIGAME_VIEW_2
#include "MinigameView.h"
#include "MinigameLogic_2.h"
#include "Animation.h"
class MinigameView_2
{
private:
    std::shared_ptr<sf::RenderWindow> app;
    std::shared_ptr<MinigameLogic_2> miniLogic;
    sf::Sprite pizza;

    //Test Shapes
    sf::CircleShape cPizza;
    sf::Texture pizzaTexture;
    sf::RectangleShape baseCut;//model cut object to transform
    sf::RectangleShape knifeBox;

    std::vector<sf::RectangleShape> actualCuts;
    std::vector<sf::RectangleShape> playerCuts;

    sf::Font font;

    bool move = false;

public:
    MinigameView_2(std::shared_ptr<MinigameLogic_2> MinigameLogic_2, std::shared_ptr<sf::RenderWindow> app);
    void draw();
    void update(const float& deltaTime);
    void cutPizza(const float& deltaTime) { move = true; };
};

#endif
