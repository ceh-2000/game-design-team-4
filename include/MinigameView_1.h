#pragma once
#ifndef MINIGAME_VIEW_1
#define MINIGAME_VIEW_1

#include "MinigameView.h"
#include "MinigameLogic_1.h"
#include "Animation.h"
#include<string>

class MinigameView_1 {
private:
    std::shared_ptr<MinigameLogic_1> miniLogic;
    std::shared_ptr<sf::RenderWindow> app;

    sf::Texture backgroundTexture1;
    sf::Texture backgroundTexture2;
    sf::Texture backgroundTexture3;
    sf::Texture backgroundTexture4;

    sf::Texture bowlTexture;

    sf::Texture appleTexture;
    sf::Texture mouseTexture;

    sf::Font font;
    sf::Text scoreText;
    sf::Text instructionsText;

    sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f(200.0f, 100.0f));

    sf::Text outcome;
    sf::Texture satsanaTexture;
    sf::Sprite satsanaSprite;
    std::shared_ptr<Animation> satsanaAnimation;

    std::string outcomes[4][4] = {{"Try again!",                       "Perfect!",     "Almost!",                          "Try again!"},
                                  {"Are you doing that right?",        "Looks great!", "Not too bad.",                     "Are you doing that right?"},
                                  {"My readers will hear about this!", "Textbook!",    "Interesting way of doing that...", "My readers will hear about this!"},
                                  {"This is a disaster!",              "Amazing!",     "I could do better!",               "This is a disaster!"}};

public:
    MinigameView_1(std::shared_ptr<MinigameLogic_1> MinigameLogic_1, std::shared_ptr<sf::RenderWindow> app);

    void drawBackground(const int &backgroundNum);

    void drawBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes);

    void drawBowl();

    void drawStatic();

    void update(const float &deltaTime, const int &round);

    void drawScore(int score);

    void animatePostHit(const int &hitOutcome, int round, const float &deltaTime);

};

#endif
