#pragma once
#include <iostream>
#include <memory>
#include "Song.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(std::shared_ptr<Song> song);

    bool getActive() { return isActive; }

    void checkEvent(); 
    void update(float deltaTime);
    float determineNextTap(float songTime);
    float determinePrevTap(float songTime);
    void tapCheck();
    void regionCheck();

private:
    std::shared_ptr<sf::RenderWindow> app = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600, 32), "Quick Quisine", sf::Style::Titlebar | sf::Style::Close);
    std::shared_ptr<Song> song;
    bool isActive = true;

    int tapNum = 0;
    int backgroundColor = 0;
    bool isHit = false;
    bool animate;
    int counter = 0;
    
    //act and success regions vary between songs
    float actRegion = 0.45f; //defines entire hit action region for a given song
    float winRegion = 0.15f; //defines successful hit time window in action region
    float almostRegion = 0.3f; //defines near hit / near miss time window in action region

    float elapsedDuration;
    float duration = 0.075f;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectSourceSprite;

    sf::Font font;
    sf::Text resultText;
};
