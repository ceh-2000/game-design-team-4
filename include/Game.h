#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include "Song.h"
#include "MinigameLogic.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>


class Game
{
protected:
    int score = 0;
    int difficult = 1;
    int currentGame = 1;
    bool isActive = true;
	std::shared_ptr<MinigameLogic> minigameLogic;
    std::shared_ptr<sf::RenderWindow> app = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600, 32), "Quick Quisine", sf::Style::Titlebar | sf::Style::Close);

public:
    Game();
    bool getActive() { return isActive; }
};
#endif

