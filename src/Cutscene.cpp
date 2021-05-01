#include "Cutscene.h"

Cutscene::Cutscene(std::shared_ptr<sf::RenderWindow> app)
{
	this->app = app;

	if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
		std::cout << "Could not load orange_kid.ttf." << std::endl;
	}
	this->scoreText.setFont(font);
	this->scoreText.setCharacterSize(50);
	this->scoreText.setFillColor(sf::Color::Red);

	dialogueBoxRect.setPosition(50, 1000);
	dialogueBoxRect.setSize(sf::Vector2f(1100,200));
	dialogueBoxRect.setFillColor(sf::Color::Black);
	dialogueBoxRect.setOutlineColor(sf::Color(25,25,25,255));
	dialogueBoxRect.setOutlineThickness(5);
}

void Cutscene::draw()
{
	this->app->clear(sf::Color::Black);
	this->app->draw(background);
	this->app->draw(mainCharacter);
	this->app->draw(otherCharacter);
	this->app->draw(dialogueBoxRect);
	this->app->draw(scoreText);
	this->app->display();
}

void Cutscene::update(const float& dt)
{
	this->scoreText.setString("Current score is "+ std::to_string(this->score)+ ".\nPress SPACE BAR to skip.");
	draw();
}

void Cutscene::selectCutscene(const int& cutSceneNum)
{
	switch(cutSceneNum)
	{
	case 1:
		backgroundTexture.loadFromFile("../data/art/background.png");
		mcTexture.loadFromFile("../data/art/mc-cutscene.png");
		otherCharacterTexture.loadFromFile("../data/art/male-chef.png");
		dialogueBoxTexture.loadFromFile("../data/art/dialogue-box.png");
		background.setTexture(backgroundTexture);
		mainCharacter.setTexture(mcTexture);
		otherCharacter.setTexture(otherCharacterTexture);
		otherCharacter.setPosition(800,0);
	break;
	case 2:
		backgroundTexture.loadFromFile("");
		background.setTexture(backgroundTexture);
		letterScoreTexture.loadFromFile("");
		letterScore.setTexture(letterScoreTexture);
	break;
	default: break;
	}
}