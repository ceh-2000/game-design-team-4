#pragma once
#ifndef MINIGAME_VIEW_2
#define MINIGAME_VIEW_2
#include "MinigameView.h"
#include "MinigameLogic_2.h"
class MinigameView_2
{
private:
	std::shared_ptr<MinigameLogic_2> miniLogic;
	sf::Sprite pizza;
	std::vector<sf::RectangleShape> actualCuts;
	std::vector<sf::RectangleShape> playerCuts;
	
public:
	MinigameView_2(std::shared_ptr<MinigameLogic_2> MinigameLogic_2, std::shared_ptr<sf::RenderWindow> app);
	void draw(std::shared_ptr<sf::RenderWindow> window);
};

#endif