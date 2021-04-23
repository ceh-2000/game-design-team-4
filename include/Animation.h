#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <map>
#include <iostream>

class Animation {
private:
    // Deduce the row number in the sprite sheet from the sprite index
    const char *spriteNames[7] = {"apple", "mouse", "satsana", "egg", "bread", "can", "eye"};
    int frameNumber[7] = {7, 4, 3, 12, 2, 8, 6};
    int rowNumber = 0;
    int boxSize = 50;

    // Individual sprite variables
    sf::Texture spriteSheet;
    sf::IntRect boundingBox;
    sf::Sprite sprite;
    sf::Vector2f dimensions;

    // Animation specific variables
    bool loop = false;
    int counter = 0;
    float maxTimeToShowFrame = 0.1f;
    float elapsedTime = 0.0f;

public:
    Animation(const std::string &spriteName, const sf::Vector2f &dimensions, const bool &loop);

    void update(const float &deltaTime);

    void draw(std::shared_ptr<sf::RenderWindow> window);
};


#endif

//file path
//translation counter
//max frames
//time per frame


