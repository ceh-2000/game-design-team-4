#pragma once
#include <iostream>
#include "Song.h"
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

private:
    Song song;
    int tapNum;
    int backgroundColor;
};