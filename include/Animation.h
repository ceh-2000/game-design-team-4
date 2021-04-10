#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>


class Animation
{
private:
    sf::IntRect texture;
    sf::Sprite sprite;
    sf::Text text;

    float elapsedDuration;
    float duration;
    bool animate = true;
    bool loop;
    int counter = 0;
    int frames;
    float timePerFrame;
public:
    Animation(bool& animate, float& elapsedDuration, int frames, float timePerFrame, bool loop, sf::Text &text, sf::Sprite &sprite, sf::IntRect &rectText);
    void animateSprite(const float& deltaTime, std::shared_ptr<sf::RenderWindow> window);
    void isLoop(bool loop) { this->loop = loop; }
    void draw(std::shared_ptr<sf::RenderWindow> window);
};





#endif

//file path
//translation counter
//max frames
//time per frame


