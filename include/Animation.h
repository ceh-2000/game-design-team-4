#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>


class Animation
{
private:
    sf::Sprite &sprite;
    sf::IntRect textureRect;
    sf::Text text;

    int startY;
    int frames;
    int frameX;
    int frameY;
    float timePerFrame;
    float elapsedDuration;
    bool loop;
    int counter;

public:
    Animation(sf::Sprite& sprite, int row, int frames, int frameX, int frameY, float timePerFrame, bool loop);
    void animate(const float& dt, std::shared_ptr<sf::RenderWindow> window);
    void animate(sf::Text& text, const float& dt, std::shared_ptr<sf::RenderWindow> window);
};
#endif