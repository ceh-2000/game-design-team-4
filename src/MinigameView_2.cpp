#include "MinigameView_2.h"

MinigameView_2::MinigameView_2(std::shared_ptr<MinigameLogic_2> MinigameLogic_2, std::shared_ptr<sf::RenderWindow> app)
{
	this->miniLogic = MinigameLogic_2;
}