#include "MinigameView_1.h"

MinigameView_1::MinigameView_1(std::shared_ptr<MinigameLogic_1> miniLogic, std::shared_ptr<sf::RenderWindow> app)
{
    this->app = app;
    this->miniLogic = miniLogic;
    this->circle.setPosition(app->getSize().x / 2.0f - circle.getRadius()*2, app->getSize().y / 2.0f);
//    this->circle.setCenter(30, 30);
    this->circle.setScale(2, 1);

}

void MinigameView_1::draw()
{
    app->draw(this->circle);
}

/*
Redraw all of our current beat boxes
*/
void MinigameView_1::updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes) {
    std::vector<bool> isGoodVector = this->miniLogic->getIsGoodVector();
    int counter = 0;
    for (BeatBoxLogic beatBox : beatBoxes) {
        sf::RectangleShape box;
        box.setSize(this->miniLogic->getIngredDim());

        bool isGood = isGoodVector.at(counter);
        sf::Color color = sf::Color::Magenta;
        if(isGood == false){
            color = sf::Color::Black;
        }

        box.setFillColor(color);
        box.setPosition(beatBox.getCurPos().x-this->miniLogic->getIngredDim().x/2, beatBox.getCurPos().y-this->miniLogic->getIngredDim().y/2);
        app->draw(box);

        counter ++;
    }
}

void MinigameView_1::update(const float& deltaTime)
{
    this->miniLogic->updateBeatBoxes(deltaTime);
    draw();
    updateBeatBoxes(this->miniLogic->getBeatBoxes());

}