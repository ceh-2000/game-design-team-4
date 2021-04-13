#pragma once
#ifndef MINIGAME_VIEW_3
#define MINIGAME_VIEW_3
#include "MinigameView.h"
#include "MinigameLogic_3.h"
class MinigameView_3 : public MinigameView
{
private:
	std::shared_ptr<MinigameLogic> miniLogic;
	sf::Sprite vegetable;
	std::vector<sf::RectangleShape> actualCuts;
	std::vector<sf::RectangleShape> playerCuts;
	
public:
	MinigameView_3(std::shared_ptr<MinigameLogic> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app);
	void draw(std::shared_ptr<sf::RenderWindow> window);
};
MinigameView_3::MinigameView_3(std::shared_ptr<MinigameLogic> MinigameLogic_3, std::shared_ptr<sf::RenderWindow> app) : MinigameView(app)
{
	this->miniLogic = MinigameLogic_3;
}
#endif