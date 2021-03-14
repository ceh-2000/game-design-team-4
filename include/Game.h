#pragma once
#include <iostream>
#include "Song.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(float tTime, std::string filename);
    ~Game();

    void setCurrentSong(std::string filename);
    void update(sf::RenderWindow& app, float deltaTime);

private:
    Song song;
    float tapTime;
};