#include "MinigameView_4.h"

MinigameView_4::MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app)
{
	this->miniLogic = MinigameLogic_4;
	this->app = app;

	for(float iter = 0.25f; iter<1.25f; iter+=0.25f)
	{
		sf::RectangleShape endPoint = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
		endPoint.setPosition(300.0f*iter + 700.0f, 100.0f);
		endPoints.push_back(endPoint);
	}
}

void MinigameView_4::draw(){

	for(int i = 0; i < 4; i++)
	{
		endPoints.at(i).setFillColor(sf::Color(i*16));
		app->draw(endPoints.at(i));
	}
}

void MinigameView_4::updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes) {
    for (BeatBoxLogic beatBox : beatBoxes) {
        sf::RectangleShape box;
        box.setSize(sf::Vector2f(50.0f, 50.0f));
        box.setFillColor(sf::Color::White);
        box.setPosition(beatBox.getCurPos());
        app->draw(box);
    }
}



void MinigameView_4::update(const float& deltaTime){

	this->miniLogic->updateBeatBoxes(deltaTime);
    updateBeatBoxes(this->miniLogic->getBeatBoxes());
	draw();

}