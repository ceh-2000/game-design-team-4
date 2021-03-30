#pragma once
#include <iostream>
#include "Song.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(std::string filename);
    ~Game();

    void setCurrentSong(std::string filename);
    void update(sf::RenderWindow& app, float deltaTime);
    float determineNextTap(float songTime);
    float determinePrevTap(float songTime);
    void tapCheck(sf::RenderWindow &app);
    void regionCheck();

private:
    Song song;
    int tapNum;
    int backgroundColor;
    bool isHit;
    bool animate;
    int counter;
    
    //act and success regions vary between songs
    float actRegion; //defines entire hit action region for a given song
    float winRegion; //defines successful hit time window in action region
    float almostRegion; //defines near hit / near miss time window in action region

    float elapsedDuration;
    float duration;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectSourceSprite;

    sf::Font font;
    sf::Text resultText;
};
