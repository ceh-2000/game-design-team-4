#pragma once
#ifndef MINIGAME_VIEW_H
#define MINIGAME_VIEW_H

#include "MinigameView_1.h"
#include "MinigameView_2.h"
#include "MinigameView_3.h"
#include "MinigameView_4.h"
#include "MinigameLogic.h"

class MinigameView
{
private:
    std::shared_ptr<MinigameLogic> logic;
    std::shared_ptr<sf::RenderWindow> app;

    sf::Texture background;
	std::vector<std::string> backgroundPaths;
	sf::Texture texture;
	sf::Font font;
	sf::IntRect rectSourceSprite;


public:
    MinigameView(std::shared_ptr<MinigameLogic> logic, std::shared_ptr<sf::RenderWindow> app);
    void update(const float& deltaTime);

	void updateBeatBoxes(const std::vector<BeatBoxLogic>& beatBoxes);
	void drawSprite(int row, sf::Vector2f position, sf::Vector2f size);
	void updateBackground(int backgroundColor);
	void draw();
};
#endif