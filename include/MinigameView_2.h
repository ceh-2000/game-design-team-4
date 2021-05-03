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

    sf::Texture satsanaTexture;
	sf::Sprite satsanaSprite;
    std::shared_ptr<Animation> satsanaAnimation;
    sf::Text outcome;

	std::string outcomes[4][4] = {{"Try again!", "Perfect!", "Almost!", "Try again!"},
							{"Are you doing that right?", "Looks great!", "Not too bad.", "Are you doing that right?"},
							{"My readers will hear about this!", "Textbook!", "Interesting way of doing that...", "My readers will hear about this!"},
							{"This is a disaster!", "Amazing!", "I could do better!", "This is a disaster!"}};

public:
    MinigameView_2(std::shared_ptr<MinigameLogic_2> MinigameLogic_2, std::shared_ptr<sf::RenderWindow> app);
    void draw();
    void update(const float& deltaTime);
    void cutPizza(const float& deltaTime) { move = true; };
    void animatePostHit(const int& hitOutcome, int round, const float& deltaTime);
};

#endif
