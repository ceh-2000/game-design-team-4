#pragma once
#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <SFML/Graphics.hpp>
#include <memory>

class Cutscene
{
private:
    std::shared_ptr<sf::RenderWindow> app;
    sf::IntRect textRect;
    sf::Texture texture;
    sf::Sprite mainCharacter;
    sf::Sprite background;
    sf::Sprite otherCharacter;
    
public:
    Cutscene(std::shared_ptr<sf::RenderWindow> app);
};
#endif