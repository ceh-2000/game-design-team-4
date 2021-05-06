#pragma once
#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Cutscene {
private:
    std::shared_ptr<sf::RenderWindow> app;

    sf::Font font;
    sf::Text scoreText;
    std::string dialogueStr;
    int score = 0;
    std::string rank;
    std::string name = "Chef";
    std::string chefName = "Guy Fieri";
    int dialogueStrIter = 0;
    float elapsedTime = 0;

    sf::Text chefText;
    std::string chefStr = "";
    int chefStrIter = 0;

    sf::Texture mcTexture;
    sf::Texture backgroundTexture;
    sf::Texture otherCharacterTexture;
    sf::Texture dialogueBoxTexture;
    sf::Texture letterScoreTexture;
    sf::Sprite dialogueBox;
    sf::Sprite mainCharacter;
    sf::Sprite background;
    sf::Sprite otherCharacter;
    sf::Sprite letterScore;
    sf::Texture satsanaTexture;
    sf::Sprite satsanaSprite;
    std::shared_ptr<Animation> satsanaAnimation;
    std::string outcomes[4][4] = {{"Try again!",                       "Perfect!",     "Almost!",                          "Try again!"},
                                  {"Are you doing that right?",        "Looks great!", "Not too bad.",                     "Are you doing that right?"},
                                  {"My readers will hear about this!", "Textbook!",    "Interesting way of doing that...", "My readers will hear about this!"},
                                  {"This is a disaster!",              "Amazing!",     "I could do better!",               "This is a disaster!"}};

public:
    Cutscene(std::shared_ptr<sf::RenderWindow> app);

    void draw(const int &cutsceneNum);

    void setFinalChefName(std::string c) { this->chefName = c; }

    void setName(std::string n) { this->name = n; }

    void setScore(int s) { this->score = s; }

    void setRank(std::string r) { this->rank = r; }

    void update(const float &dt, const int &cutSceneNum);

    void selectCutscene(const int &cutSceneNum);
};

#endif
