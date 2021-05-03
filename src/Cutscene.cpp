#include "Cutscene.h"

Cutscene::Cutscene(std::shared_ptr<sf::RenderWindow> app)
{
	this->app = app;

	if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
		std::cout << "Could not load orange_kid.ttf." << std::endl;
	}
	this->scoreText = sf::Text("",font, 50);
	this->scoreText.setFillColor(sf::Color::White);
}

void Cutscene::draw()
{
	this->app->clear();
	this->app->draw(background);
	this->app->draw(mainCharacter);
	this->app->draw(otherCharacter);
	this->app->draw(dialogueBox);
	this->app->draw(scoreText);
	this->app->display();
}

void Cutscene::update(const float& dt)
{
	if(dialogueStrIter < dialogueStr.length()-1)
	{
		if(elapsedTime > 0.05f)
		{
			this->scoreText.setString(scoreText.getString()+dialogueStr[dialogueStrIter]);
			dialogueStrIter++;
			elapsedTime = 0;
		}
		elapsedTime += dt;
	}
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
		dialogueBoxTexture.loadFromFile("../data/art/dialogueBox.png");
		background.setTexture(backgroundTexture);
		mainCharacter.setTexture(mcTexture);
		otherCharacter.setTexture(otherCharacterTexture);
		dialogueBox.setTexture(dialogueBoxTexture);
		otherCharacter.setPosition(800,0);
		dialogueBox.setPosition(0, 600);
		scoreText.setPosition(dialogueBox.getPosition().x+50, dialogueBox.getPosition().y+25);
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