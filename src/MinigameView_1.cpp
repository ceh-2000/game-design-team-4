#include "MinigameView_1.h"

MinigameView_1::MinigameView_1(std::shared_ptr<MinigameLogic_1> miniLogic, std::shared_ptr<sf::RenderWindow> app)
{
    this->app = app;
    this->miniLogic = miniLogic;
    float scale = this->miniLogic->getBowlSize().x / this->miniLogic->getBowlSize().y;
    this->circle.setScale(scale, 1);
    this->circle.setPosition(this->miniLogic->getBowlPosition());

}

void MinigameView_1::drawBowl()
{
    this->circle.setPosition(this->miniLogic->getBowlPosition());
    app->draw(this->circle);
}

/*
Redraw all of our current beat boxes
*/
void MinigameView_1::drawBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes) {
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
    this->miniLogic->updateBowl(deltaTime);
    drawBowl();
    drawBeatBoxes(this->miniLogic->getBeatBoxes());

}