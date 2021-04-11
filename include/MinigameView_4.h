#pragma once
#ifndef MINIGAME_VIEW_4
#define MINIGAME_VIEW_4
#include "MinigameView.h"
#include "MinigameLogic_4.h"
class MinigameView_4 : public MinigameView
{
private:
	std::shared_ptr<MinigameLogic> miniLogic;
	sf::Sprite chef;
	sf::Sprite oven;
	sf::Sprite refrigerator;
	sf::Sprite counter;
	sf::Sprite stove;
	
public:
	MinigameView_4(std::shared_ptr<MinigameLogic> MinigameLogic_4);
	void draw(std::shared_ptr<sf::RenderWindow> window);
};
MinigameView_4::MinigameView_4(std::shared_ptr<MinigameLogic> MinigameLogic_4) : MinigameView(MinigameLogic_4)
{
	this->miniLogic = MinigameLogic_4;
}
#endif