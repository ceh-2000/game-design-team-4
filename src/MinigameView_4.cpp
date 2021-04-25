#include "MinigameView_4.h"

MinigameView_4::MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app)
{
	this->miniLogic = MinigameLogic_4;
	this->app = app;

	texture.loadFromFile("../data/art/arrows-spritesheet.png");

	refrigerator = sf::Sprite(texture, sf::IntRect(0,64,64,64));
	counter = sf::Sprite(texture, sf::IntRect(0,128,64,64));
	oven = sf::Sprite(texture, sf::IntRect(0,192,64,64));
	stove = sf::Sprite(texture, sf::IntRect(0,256,64,64));

	int count = 0;
	for(float iter = 0.25f; iter<1.25f; iter+=0.25f)
	{
		sf::Sprite endPoint = sf::Sprite(texture);
		endPoint.setTextureRect(sf::IntRect(count,0,64,64));
		endPoint.setPosition(300.0f*iter+750.0f, 100.0f);
		endPoints.push_back(endPoint);
		count+=64;
	}

	refrigerator.setPosition(100, 150);
	counter.setPosition(200, 250);
	oven.setPosition(200, 50);
	stove.setPosition(300, 150);

	tables.push_back(refrigerator);
	tables.push_back(counter);
	tables.push_back(oven);
	tables.push_back(stove);
}

//TODO: Add 4 squares in a cross with the chef in the middle
//have the chef move to a designated input's direction (LEFT, RIGHT, UP, DOWN)
void MinigameView_4::reachInput(const int& input, const int& tapOutcome)
{	
	
	switch(tapOutcome) // set what sprite is done and where the chef is, set score as well
	{
		case 3: //miss
			this->miniLogic->setScore(-50);
			
			break;
		case 2: //almost
			this->miniLogic->setScore(20);

			break;
		case 1: //perfect!
			this->miniLogic->setScore(50);
			
			break;
	}
	for (int i = 0; i<4; i++) //reset all inputs again
	{
		tables.at(i).setTextureRect(sf::IntRect(0,i*64+64,64,64));
	}

	int left = 64;
	int top = 0;
	switch(input)
	{
		//Left = 0, Down = 1, Up = 2, Right = 3
		case 0: // Left
			top=64;
			tables.at(0).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		case 1: // Down
			top=128;
			tables.at(1).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		case 2: // Up
			top=192;
			tables.at(2).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		case 3: // Right
			top=256;
			tables.at(3).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		case 4: // Up and Right
			top=192;
			tables.at(2).setTextureRect(sf::IntRect(left,top,64,64));
			top=256;
			tables.at(3).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		case 5: // Down and Right
			top=128;
			tables.at(1).setTextureRect(sf::IntRect(left,top,64,64));
			top=256;
			tables.at(3).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		case 6: // Left and Right
			top=64;
			tables.at(0).setTextureRect(sf::IntRect(left,top,64,64));
			top=256;
			tables.at(3).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		case 7: // Down and Left
			top=128;
			tables.at(1).setTextureRect(sf::IntRect(left,top,64,64));
			top=64;
			tables.at(0).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		case 8: // Down and Up
			top=128;
			tables.at(1).setTextureRect(sf::IntRect(left,top,64,64));
			top=192;
			tables.at(2).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		case 9: // Right and Left
			top=256;
			tables.at(3).setTextureRect(sf::IntRect(left,top,64,64));
			top=64;
			tables.at(0).setTextureRect(sf::IntRect(left,top,64,64));
			break;
		default:
			break;
	}
}

void MinigameView_4::resetInput()
{
}

void MinigameView_4::updateBeatBoxes(std::vector<std::shared_ptr<BeatBoxLogic>> beatBoxes) 
{
	// int count = 0;
	for (std::shared_ptr<BeatBoxLogic> beatBox : beatBoxes) 
	{
		sf::Sprite arrow = sf::Sprite(texture);
		arrow.setPosition(beatBox->getCurPos());
		switch(int(arrow.getPosition().x))
		{
			case 825: arrowTextureRect.left = 0; break;
			case 900: arrowTextureRect.left = 64; break;
			case 975: arrowTextureRect.left = 128; break;
			case 1050: arrowTextureRect.left = 192;	break;
			default: break;
		}
		if(arrow.getPosition().y == 34.0f)
		{
			// std::vector<std::shared_ptr<BeatBoxLogic>>::iterator iter;
			// iter+=count;
			// beatBoxes.erase(iter);

			arrowTextureRect.left = 256;
			arrow.setTextureRect(arrowTextureRect);
		}
		arrow.setTextureRect(arrowTextureRect);
		app->draw(arrow);
		
		// count++;
	}
}

//draws squares to show when inputs reach endpoints
void MinigameView_4::draw()
{
	app->clear(sf::Color(255,128,255,255));
	for(int i = 0; i < 4; i++)
	{
		app->draw(endPoints.at(i));
		app->draw(tables.at(i));
	}
}

void MinigameView_4::update(const float& deltaTime)
{
	this->miniLogic->updateBeatBoxes(deltaTime);
	draw();
	updateBeatBoxes(this->miniLogic->getBeatBoxes());
}