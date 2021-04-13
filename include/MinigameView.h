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
	sf::Texture texture;
	sf::Font font;
	sf::IntRect rectSourceSprite;
	
public:
	MinigameView(std::shared_ptr<sf::RenderWindow> app);
	void updateBeatBoxes(const std::vector<BeatBoxLogic>& beatBoxes);
	void drawSprite(int row, sf::Vector2f position, sf::Vector2f size);
	void updateBackground(int backgroundColor);
	void draw();
	// std::shared_ptr<sf::RenderWindow> window
};
#endif