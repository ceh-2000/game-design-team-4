#pragma once
#ifndef MINIGAME_VIEW_H
#define MINIGAME_VIEW_H
#include <iostream>
#include <memory>
#include "BeatBoxLogic.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class MinigameView : std::enable_shared_from_this<MinigameView>
{
private:
	sf::Texture background;
	std::vector<std::string> backgroundPaths;
	std::shared_ptr<sf::RenderWindow> app;
	
public:
	MinigameView(std::shared_ptr<sf::RenderWindow> app);
	void updateBackground(int backgroundColor);
	void updateBeatBoxes(const std::vector<BeatBoxLogic>& beatBoxes);
	void drawSprite(int row, sf::Vector2f position, sf::Vector2f size);
	void draw();
	// std::shared_ptr<sf::RenderWindow> window
};
#endif