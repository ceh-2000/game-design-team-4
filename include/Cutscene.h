#pragma once
#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

class Cutscene
{
private:
    std::shared_ptr<sf::RenderWindow> app;

    sf::Font font;
    sf::Text scoreText;
    std::string dialogueStr;
    int score = 0;
    std::string rank;
    int dialogueStrIter = 0;
    float elapsedTime = 0;

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

public:
    Cutscene(std::shared_ptr<sf::RenderWindow> app);
    void draw();
    void setScore(int s) { this->score = s;}
    void setRank(std::string r) {this->rank = r;}
    void update(const float& dt);
    void selectCutscene(const int& cutSceneNum);
};
#endif
