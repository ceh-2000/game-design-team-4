#include "MinigameView_4.h"

MinigameView_4::MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app)
{
	this->miniLogic = MinigameLogic_4;
	this->app = app;

	for(float iter = 0.25f; iter<1.25f; iter+=0.25f)
	{
		sf::RectangleShape endPoint = sf::RectangleShape(sf::Vector2f(50.0f, 50.0f));
		endPoint.setPosition(300.0f*iter+750.0f, 100.0f);
		endPoints.push_back(endPoint);
	}
	sf::Vector2f position = sf::Vector2f(app->getSize().x/2.0f, app->getSize().y/2.0f);

	// oven.setPosition(app->getSize().x/2.0f, app->getSize().y/2.0f);

	oven.setPosition(1*blockSize.x , 0);
	refrigerator.setPosition(0, 1*blockSize.y);
	counter.setPosition(1*blockSize.x, 2*blockSize.y);
	stove.setPosition(2*blockSize.x, 1*blockSize.y);
}

//TODO: Add 4 squares in a cross with the chef in the middle
//have the chef move to a designated input's direction (LEFT, RIGHT, UP, DOWN)

//draws squares to show when inputs reach endpoints
void MinigameView_4::draw()
{
	for(int i = 0; i < 4; i++)
	{
		endPoints.at(i).setFillColor(sf::Color(i*16));
		app->draw(endPoints.at(i));
	}

	app->draw(oven);
	app->draw(refrigerator);
	app->draw(counter);
	app->draw(stove);	
}

void MinigameView_4::updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes) 
{
	sf::RectangleShape box;
    for (BeatBoxLogic beatBox : beatBoxes) 
	{        
        box.setSize(sf::Vector2f(50.0f, 50.0f));
        box.setFillColor(sf::Color::White);
        box.setPosition(beatBox.getCurPos());
		if(box.getPosition().y == 100.0f)
		{
			for(auto end : endPoints)
				if(box.getPosition().x == end.getPosition().x)
				{
					box.setFillColor(sf::Color::Transparent);
					switch(int(end.getPosition().x))
					case 825:
					break;

				}
		}
		app->draw(box);
    }
}



void MinigameView_4::update(const float& deltaTime)
{
	this->miniLogic->updateBeatBoxes(deltaTime);
	draw();
    updateBeatBoxes(this->miniLogic->getBeatBoxes());

}