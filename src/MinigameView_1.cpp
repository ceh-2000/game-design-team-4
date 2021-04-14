#include "MinigameView_1.h"

MinigameView_1::MinigameView_1(std::shared_ptr<MinigameLogic_1> miniLogic, std::shared_ptr<sf::RenderWindow> app)
{
    this->app = app;
    this->miniLogic = miniLogic;
    this->circle.setPosition(app->getSize().x / 2.0f, app->getSize().y / 2.0f);

}

void MinigameView_1::draw()
{
    app->draw(this->circle);
}

/*
Redraw all of our current beat boxes
*/
void MinigameView_1::updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes) {
    for (BeatBoxLogic beatBox : beatBoxes) {
        sf::RectangleShape box;
        box.setSize(sf::Vector2f(50, 50));
        box.setFillColor(sf::Color::Magenta);
        box.setPosition(beatBox.getCurPos());
        app->draw(box);
    }
}

void MinigameView_1::update(const float& deltaTime)
{
    this->miniLogic->updateBeatBoxes(deltaTime);
    updateBeatBoxes(this->miniLogic->getBeatBoxes());

    draw();
}