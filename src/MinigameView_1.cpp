#include "MinigameView_1.h"

MinigameView_1::MinigameView_1(std::shared_ptr<MinigameLogic_1> MinigameLogic_1, std::shared_ptr<sf::RenderWindow> app)
{
    this->app = app;
    this->miniLogic = MinigameLogic_1;
    this->circle.setPosition(app->getSize().x / 2.0f, app->getSize().y / 2.0f);
}

void MinigameView_1::draw()
{
    app->clear();
    app->draw(this->circle);
    app->display();
}

void MinigameView_1::update(const float& deltaTime)
{
    draw();
}