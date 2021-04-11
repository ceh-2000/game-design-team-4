#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include "Song.h"
#include "BeatBoxLogic.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(std::shared_ptr<Song> song);

    bool getActive() { return isActive; }
    float determineNextTap(float songTime);
    float determinePrevTap(float songTime);

    void update(const float& deltaTime);
    void tapCheck();
	void checkEvent(); 
    void regionCheck();
    void updateBeatBoxes(const float& deltaTime);

private:
    std::shared_ptr<sf::RenderWindow> app = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600, 32), "Quick Quisine", sf::Style::Titlebar | sf::Style::Close);
    std::shared_ptr<Song> song;
    bool isActive = true;

    // Variables for before a hit occurs
    std::vector<BeatBoxLogic> beatBoxes;

    // Variable to detect and respond to hits
    int tapNum = 0;
    int backgroundColor = 0;
    bool isHit = false;
    bool animate;
    int counter = 0;
    bool resetHitYet = false;

    // Act and success regions vary between songs
    float actRegion = 0.45f;   //defines entire hit action region for a given song
    float winRegion = 0.15f;   //defines successful hit time window in action region
    float almostRegion = 0.3f; //defines near hit / near miss time window in action region

    float elapsedDuration;
    float duration = 0.075f;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectSourceSprite;

    sf::Font font;
    sf::Text resultText;

	

};
#endif

