#include "MinigameView_4.h"

MinigameView_4::MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app)
{
	this->miniLogic = MinigameLogic_4;
	this->app = app;
	// this->score.setPosition(app->getSize().x/2.0f, app->getSize().y/2.0f);

	texture.loadFromFile("../data/art/arrows-spritesheet.png");
	font.loadFromFile("../data/fonts/orange_kid.ttf");

	chef = sf::Sprite(texture, sf::IntRect(0,320,256,256));
	refrigerator = sf::Sprite(texture, sf::IntRect(0,256,64,64));
	counter = sf::Sprite(texture, sf::IntRect(0,320,64,64));
	oven = sf::Sprite(texture, sf::IntRect(0,384,64,64));
	stove = sf::Sprite(texture, sf::IntRect(0,448,64,64));

	int count = 0;
	for(float iter = 0.25f; iter<1.25f; iter+=0.25f)
	{
		sf::Sprite endPoint = sf::Sprite(texture);
		endPoint.setTextureRect(sf::IntRect(0,count,64,64));
		endPoint.setPosition(300.0f*iter+750.0f, 100.0f);
		endPoints.push_back(endPoint);
		count+=64;
	}

	backBoard.setSize(sf::Vector2f(310.0f,app->getSize().y));
	backBoard.setPosition(sf::Vector2f(endPoints.at(0).getPosition().x - 10.0f, 0));
	backBoard.setFillColor(sf::Color(30,30,30,255));
	placeholder.setSize(sf::Vector2f(126+750, 800));
	placeholder.setPosition(sf::Vector2f(126, 0));

	//2 = 0
	refrigerator.setPosition(2, 128);
	counter.setPosition(66, 192);
	oven.setPosition(66, 64);
	stove.setPosition(126, 128);

	tables.push_back(refrigerator);
	tables.push_back(counter);
	tables.push_back(oven);
	tables.push_back(stove);
}

//TODO: Add 4 squares in a cross with the chef in the middle
//have the chef move to a designated input's direction (LEFT, RIGHT, UP, DOWN)
void MinigameView_4::reachInput(const int& input, const int& tapOutcome)
{
	this->miniLogic->setScore(tapOutcome);
	for (int i = 0; i<4; i++) //reset all inputs again
	{
		tables.at(i).setTextureRect(sf::IntRect(0,i*64+256,64,64));
		endPoints.at(i).setTextureRect(sf::IntRect(0,i*64,64,64));

	}
	int left = 64;
	switch(input)
	{
		//Left = 0, Down = 1, Up = 2, Right = 3
		case 4: // Up and Right
			tables.at(2).setTextureRect(sf::IntRect(left,192,64,64));
			tables.at(3).setTextureRect(sf::IntRect(left,256,64,64));
			break;
		case 5: // Down and Right
			tables.at(1).setTextureRect(sf::IntRect(left,128,64,64));
			tables.at(3).setTextureRect(sf::IntRect(left,256,64,64));
			break;
		case 6: // Left and Right
			tables.at(0).setTextureRect(sf::IntRect(left,64,64,64));
			tables.at(3).setTextureRect(sf::IntRect(left,256,64,64));
			break;
		case 7: // Down and Left
			tables.at(1).setTextureRect(sf::IntRect(left,128,64,64));
			tables.at(0).setTextureRect(sf::IntRect(left,64,64,64));
			break;
		case 8: // Down and Up
			tables.at(1).setTextureRect(sf::IntRect(left,128,64,64));
			tables.at(2).setTextureRect(sf::IntRect(left,192,64,64));
			break;
		case 9: // Right and Left
			tables.at(3).setTextureRect(sf::IntRect(left,256,64,64));
			tables.at(0).setTextureRect(sf::IntRect(left,64,64,64));
			break;
		default: 
			tables.at(input).setTextureRect(sf::IntRect(left,256+input*64,64,64));
			endPoints.at(input).setTextureRect(sf::IntRect(left,input*64,64,64));
		break;
	}
		score.setString("Score: " + std::to_string(this->miniLogic->getScore()));
}

void MinigameView_4::updateBeatBoxes(std::vector<std::shared_ptr<BeatBoxLogic>> beatBoxes)
{
	for (std::shared_ptr<BeatBoxLogic> beatBox : beatBoxes)
	{
		arrow = std::make_shared<sf::Sprite>(texture);
		arrow->setPosition(beatBox->getCurPos());
		switch(int(arrow->getPosition().x))
		{
			case 825: arrowTextureRect.top = 0; break;
			case 900: arrowTextureRect.top = 64; break;
			case 975: arrowTextureRect.top = 128; break;
			case 1050: arrowTextureRect.top = 192;	break;
			default: break;
		}
		if(arrow->getPosition().y > 36.0f)
		{
			arrow->setTextureRect(arrowTextureRect);
			app->draw(*arrow);
		}
	}
}

//draws squares to show when inputs reach endpoints
void MinigameView_4::draw()
{
	app->clear(sf::Color(0,0,0,255));
	app->draw(placeholder);
	app->draw(backBoard);
	for(int i = 0; i < 4; i++)
	{
		app->draw(endPoints.at(i));
		app->draw(tables.at(i));
	}
	// app->draw(chef);
	app->draw(score);
}

void MinigameView_4::update(const float& dt)
{
	draw();
	this->miniLogic->updateBeatBoxes(dt);
	updateBeatBoxes(this->miniLogic->getBeatBoxes());
}