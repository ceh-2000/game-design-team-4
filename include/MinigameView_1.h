#pragma once
#ifndef MINIGAME_VIEW_1
#define MINIGAME_VIEW_1
#include "MinigameView.h"
#include "MinigameLogic_1.h"
class MinigameView_1 : public MinigameView
{
private:
	std::shared_ptr<MinigameLogic> miniLogic;
	sf::Sprite bowl;
	sf::Sprite ingredient;
	
public:
	MinigameView_1(std::shared_ptr<MinigameLogic> MinigameLogic_1, std::shared_ptr<sf::RenderWindow> app);
	void draw(std::shared_ptr<sf::RenderWindow> window);
};
#endif