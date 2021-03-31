#pragma once
#ifndef MINIGAME_VIEW_2
#define MINIGAME_VIEW_2
#include "MinigameView.h"
#include "MinigameLogic_2.h"
class MinigameView_2 : public MinigameView
{
private:
	std::shared_ptr<MinigameLogic> miniLogic;
	sf::Sprite pizza;
	std::vector<sf::RectangleShape> actualCuts;
	std::vector<sf::RectangleShape> playerCuts;
	
public:
	MinigameView_2(std::shared_ptr<MinigameLogic> MinigameLogic_2);
	void draw(std::shared_ptr<sf::RenderWindow> window);
};
MinigameView_2::MinigameView_2(std::shared_ptr<MinigameLogic> MinigameLogic_2) : MinigameView(MinigameLogic_2)
{
	this->miniLogic = MinigameLogic_2;
}
#endif