#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include "Song.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "MinigameLogic.h"
#include "MinigameView.h"
#include "Cutscene.h"
#include "MainMenu.h"

class Game
{
protected:
    std::vector<std::vector<std::string>> scoreRank = {{" "," "," "," "},{" "," "," "," "},{" "," "," "," "},{" "," "," "," "}};
    std::vector<std::string> roundRank = {" "," "," "," "};
    int score = 0;
    int round = 0;
    int currentGame = 6;
    bool isActive = true;
    float minigameTime = 30.0f;
    int numOfRounds = 3;
    float elapsedTime = 0.0f;
    bool left, down, up, right;

    std::shared_ptr<Song> song;
	   std::shared_ptr<MinigameLogic> logic;
    std::shared_ptr<MinigameView> view;
    std::shared_ptr<sf::RenderWindow> app = std::make_shared<sf::RenderWindow>(sf::VideoMode(1200, 800, 32), "Quick Quisine", sf::Style::Titlebar | sf::Style::Close);
    std::shared_ptr<Cutscene> cut_scene;
    std::shared_ptr<MainMenu> main_menu;

    std::shared_ptr<MinigameView_1> view_1;
    std::shared_ptr<MinigameView_2> view_2;
    std::shared_ptr<MinigameView_3> view_3;
    std::shared_ptr<MinigameView_4> view_4;

    std::shared_ptr<MinigameLogic_1> logic_1;
    std::shared_ptr<MinigameLogic_2> logic_2;
    std::shared_ptr<MinigameLogic_3> logic_3;
    std::shared_ptr<MinigameLogic_4> logic_4;


public:
    Game(std::shared_ptr<Song> audio);
    bool getActive() { return isActive; }
    void update(const float &deltaTime);
    void checkEvent(const float& deltaTime);
    int multiArrowInput();
    void switchToNewGame();

    void minigame1EventHandler(const float &deltaTime, sf::Event event);
    void minigame2EventHandler(const float &deltaTime, sf::Event event);
    void minigame3EventHandler(const float &deltaTime, sf::Event event);
    void minigame4EventHandler(const float &deltaTime, sf::Event event);
    void mainMenuEventHandler(const float &deltaTime, sf::Event event);

    void endRound();
    void calcRoundRank ();
};
#endif
