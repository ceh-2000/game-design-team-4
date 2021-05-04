#include "MinigameView_4.h"

MinigameView_4::MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app)
{
	this->miniLogic = MinigameLogic_4;
	this->app = app;
	// this->score.setPosition(app->getSize().x/2.0f, app->getSize().y/2.0f);

	texture.loadFromFile("../data/art/arrows-spritesheet.png");
	font.loadFromFile("../data/fonts/orange_kid.ttf");
	satsanaTexture.loadFromFile("../data/art/SatsanaSheet.png");

	chef = sf::Sprite(texture, sf::IntRect());
	chef_2 = sf::Sprite(texture, sf::IntRect());
	refrigerator = sf::Sprite(texture, sf::IntRect(0,256,128,128));
	counter = sf::Sprite(texture, sf::IntRect(0,384,128,128));
	oven = sf::Sprite(texture, sf::IntRect(0,512,128,128));
	stove = sf::Sprite(texture, sf::IntRect(0,640,128,128));

	satsanaSprite.setTexture(satsanaTexture);
	satsanaSprite.setPosition(10,680);

	satsanaAnimation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, false);
	outcome.setFont(font);
	outcome.setCharacterSize(48);
	outcome.setFillColor(sf::Color::White);
	outcome.setPosition(sf::Vector2f(115, 680));

	int count = 0;
	for(int i = 0; i<4; i++)
	{
		sf::Sprite endPoint = sf::Sprite(texture);
		endPoint.setTextureRect(sf::IntRect(0,count,64,64));
		endPoint.setPosition(75*i+825, 100.0f);
		endPoints.push_back(endPoint);
		count+=64;
	}

	backBoard.setSize(sf::Vector2f(310.0f,app->getSize().y));
	backBoard.setPosition(sf::Vector2f(endPoints.at(0).getPosition().x - 10.0f, 0));
	backBoard.setFillColor(sf::Color(30,30,30,255));

	//2 = 0
	refrigerator.setPosition(194, 256);
	counter.setPosition(322, 384);
	oven.setPosition(322, 128);
	stove.setPosition(446, 256);
	chef.setPosition(66, 256);
	chef_2.setPosition(322, 256);

	tables.push_back(refrigerator);
	tables.push_back(counter);
	tables.push_back(oven);
	tables.push_back(stove);
}

void MinigameView_4::resetSprites()
{
	elapsedTime = 0;
	for (int i = 0; i<4; i++) //reset all inputs again
	{
		tables.at(i).setTextureRect(sf::IntRect(0,i*128+256,128,128));
		endPoints.at(i).setTextureRect(sf::IntRect(0,i*64,64,64));
	}
	chef.setTextureRect(sf::IntRect());
	chef_2.setTextureRect(sf::IntRect());
}

//TODO: Add 4 squares in a cross with the chef in the middle
//have the chef move to a designated input's direction (LEFT, RIGHT, UP, DOWN)
void MinigameView_4::reachInput(const int& input, const int& tapOutcome)
{
	resetSprites();
	this->miniLogic->setScore(input, tapOutcome);

	switch(input)
	{
		//Left = 0, Down = 1, Up = 2, Right = 3
		case 4: // Up and Right
			tables.at(2).setTextureRect(sf::IntRect(left,512,128,128));
			tables.at(3).setTextureRect(sf::IntRect(left,640,128,128));
			endPoints.at(2).setTextureRect(sf::IntRect(64,2*64,64,64));
			endPoints.at(3).setTextureRect(sf::IntRect(64,3*64,64,64));
			chef.setTextureRect(sf::IntRect(256, 256, 256, 256)); //UP
			chef_2.setTextureRect(sf::IntRect(512, 256, 256, 256)); //RIGHT
			break;
		case 5: // Down and Right
			tables.at(1).setTextureRect(sf::IntRect(left,384,128,128));
			tables.at(3).setTextureRect(sf::IntRect(left,640,128,128));
			endPoints.at(1).setTextureRect(sf::IntRect(64,1*64,64,64));
			endPoints.at(3).setTextureRect(sf::IntRect(64,3*64,64,64));
			chef.setTextureRect(sf::IntRect(512, 0, 256, 256)); //DOWN
			chef_2.setTextureRect(sf::IntRect(512, 256, 256, 256)); //RIGHT
			break;
		case 6: // Left and Right
			tables.at(0).setTextureRect(sf::IntRect(left,256,128,128));
			tables.at(3).setTextureRect(sf::IntRect(left,640,128,128));
			endPoints.at(0).setTextureRect(sf::IntRect(64,0*64,64,64));
			endPoints.at(3).setTextureRect(sf::IntRect(64,3*64,64,64));
			chef.setTextureRect(sf::IntRect(256, 0, 256, 256)); //LEFT
			chef_2.setTextureRect(sf::IntRect(512, 256, 256, 256)); //RIGHT
			break;
		case 7: // Down and Left
			tables.at(1).setTextureRect(sf::IntRect(left,384,128,128));
			tables.at(0).setTextureRect(sf::IntRect(left,256,128,128));
			endPoints.at(1).setTextureRect(sf::IntRect(64,1*64,64,64));
			endPoints.at(0).setTextureRect(sf::IntRect(64,0*64,64,64));
			chef.setTextureRect(sf::IntRect(512, 0, 256, 256)); //DOWN
			chef_2.setTextureRect(sf::IntRect(256, 0, 256, 256)); //LEFT
			break;
		case 8: // Down and Up
			tables.at(1).setTextureRect(sf::IntRect(left,384,128,128));
			tables.at(2).setTextureRect(sf::IntRect(left,512,128,128));
			endPoints.at(1).setTextureRect(sf::IntRect(64,1*64,64,64));
			endPoints.at(2).setTextureRect(sf::IntRect(64,2*64,64,64));
			chef.setTextureRect(sf::IntRect(512, 0, 256, 256)); //DOWN
			chef_2.setTextureRect(sf::IntRect(256, 256, 256, 256)); //UP
			break;
		case 9: // Left and Up
			tables.at(0).setTextureRect(sf::IntRect(left,256,128,128));
			tables.at(2).setTextureRect(sf::IntRect(left,512,128,128));
			endPoints.at(0).setTextureRect(sf::IntRect(64,0*64,64,64));
			endPoints.at(2).setTextureRect(sf::IntRect(64,2*64,64,64));
			chef.setTextureRect(sf::IntRect(256, 0, 256, 256)); //LEFT
			chef_2.setTextureRect(sf::IntRect(256, 256, 256, 256)); //UP
			break;
		default:
			tables.at(input).setTextureRect(sf::IntRect(left,256+input*128,128,128));
			endPoints.at(input).setTextureRect(sf::IntRect(64,input*64,64,64));
			switch(input)
			{
				case 0: chef.setTextureRect(sf::IntRect(256, 0, 256, 256)); break; //LEFT
				case 1:	chef.setTextureRect(sf::IntRect(512, 0, 256, 256)); break; //DOWN
				case 2: chef.setTextureRect(sf::IntRect(256, 256, 256, 256)); break; //UP
				case 3: chef.setTextureRect(sf::IntRect(512, 256, 256, 256)); break; //RIGHT
				default: break;
			}
		break;
	}
	score.setString("Score: " + std::to_string(this->miniLogic->getScore()));
}

void MinigameView_4::updateBeatBoxes(std::vector<BeatBoxLogic> &beatBoxes)
{
	int iter = 0;
	for (BeatBoxLogic beatBox : beatBoxes)
	{
		arrow = std::make_shared<sf::Sprite>(texture);
		arrow->setPosition(beatBox.getCurPos());
		if(arrow->getPosition().y > 36.0f)
		{
			switch(int(arrow->getPosition().x))
			{
				case 825: arrowTextureRect.top = 0; break;
				case 900: arrowTextureRect.top = 64; break;
				case 975: arrowTextureRect.top = 128; break;
				case 1050: arrowTextureRect.top = 192; break;
				default: break;
			}
			arrow->setTextureRect(arrowTextureRect);
			app->draw(*arrow);
		}
	}
	this->miniLogic->setTotalScore(iter);
}

//draws squares to show when inputs reach endpoints
void MinigameView_4::draw()
{
	app->clear(sf::Color(0,0,0,255));
	app->draw(backBoard);
	for(int i = 0; i < 4; i++)
	{
		app->draw(endPoints.at(i));
		app->draw(tables.at(i));
	}
	// app->draw(chef);
	// app->draw(chef_2);
	app->draw(score);
}

void MinigameView_4::update(const float& dt)
{
	if(elapsedTime>2.0f)
		resetSprites();
	draw();
	this->miniLogic->updateBeatBoxes(dt);
	updateBeatBoxes(this->miniLogic->getBeatBoxes());
	elapsedTime += dt;
	satsanaAnimation->animate(outcome, dt, app);
}

void MinigameView_4::animatePostHit(const int& hitOutcome, int round, const float& deltaTime){

	outcome.setString(outcomes[round][hitOutcome]);
	satsanaAnimation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, false);

}