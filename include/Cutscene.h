#pragma once
#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <SFML/Graphics.hpp>
#include <memory>

class Cutscene
{
private:
    std::shared_ptr<sf::RenderWindow> app;
    sf::Texture mcTexture;
    sf::Texture backgroundTexture;
    sf::Texture otherCharacterTexture;
    sf::Texture dialogueBoxTexture;
    sf::Sprite dialogueBox;
    sf::Sprite mainCharacter;
    sf::Sprite background;
    sf::Sprite otherCharacter;
    
    sf::RectangleShape dialogueBox = sf::RectangleShape();
public:
    Cutscene(std::shared_ptr<sf::RenderWindow> app);
    void draw();
    void update(const float& dt);
    void selectCutscene(const int& cutSceneNum);
};
#endif