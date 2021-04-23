#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>


class Animation
{
private:
    sf::IntRect textureRect;
    sf::Sprite sprite;

    int row;
    int frames;
    int sizePerFrame;
    float timePerFrame;
    float elapsedDuration;
    bool loop;
<<<<<<< Updated upstream
    int counter = 0;
    int frames;
    float timePerFrame;
public:
    Animation(float& elapsedDuration, int frames, float timePerFrame, sf::Sprite &sprite, sf::IntRect &rectText);
    void animateSprite(const float& deltaTime, std::shared_ptr<sf::RenderWindow> window, sf::Text& resultText);
    void animateSprite(const float& deltaTime, std::shared_ptr<sf::RenderWindow> window);
    void isLoop(bool loop) { this->loop = loop; }
=======
    int counter;
    

public:
    Animation(sf::Sprite& sprite, int row, int frames, int sizePerFrame, float timePerFrame, bool loop);
    void isLoop(bool loop) { this->loop = loop; }
    void animate(const float& dt, std::shared_ptr<sf::RenderWindow> window);
>>>>>>> Stashed changes
};





#endif

<<<<<<< Updated upstream
//file path
//translation counter
//max frames
//time per frame
=======

>>>>>>> Stashed changes
