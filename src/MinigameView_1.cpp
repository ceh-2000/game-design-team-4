#include "MinigameView_1.h"

MinigameView_1::MinigameView_1(std::shared_ptr<MinigameLogic> MinigameLogic_1, std::shared_ptr<sf::RenderWindow> app) : MinigameView(app)
{
    this->miniLogic = MinigameLogic_1;
}