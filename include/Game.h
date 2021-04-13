#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include "Song.h"
// #include "MinigameLogic.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "MinigameLogic.h"
#include "MinigameView.h"

class Game
{
protected:
    int score = 0;
    int difficult = 1;
    int currentGame = 1;
    bool isActive = true;
	std::shared_ptr<MinigameLogic> logic;
    std::shared_ptr<MinigameView> view;
    std::shared_ptr<sf::RenderWindow> app = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600, 32), "Quick Quisine", sf::Style::Titlebar | sf::Style::Close);

    std::shared_ptr<MinigameView_1> view_1;
    std::shared_ptr<MinigameView_2> view_2;
    std::shared_ptr<MinigameView_3> view_3;
    std::shared_ptr<MinigameView_4> view_4;

    std::shared_ptr<MinigameLogic_1> logic_1;
    std::shared_ptr<MinigameLogic_2> logic_2;
    std::shared_ptr<MinigameLogic_3> logic_3;
    std::shared_ptr<MinigameLogic_4> logic_4;

public:
    Game();
    bool getActive() { return isActive; }
    void update(const float &deltaTime);
    void checkEvent();
};
#endif