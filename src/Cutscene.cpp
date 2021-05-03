#include "Cutscene.h"

Cutscene::Cutscene(std::shared_ptr<sf::RenderWindow> app)
{
	this->app = app;

	font.loadFromFile("../data/fonts/orange_kid.ttf");
	this->scoreText = sf::Text("",font, 50);
	this->scoreText.setFillColor(sf::Color::White);

	satsanaTexture.loadFromFile("../data/art/SatsanaSheet.png");
	satsanaSprite.setTexture(satsanaTexture);
    satsanaSprite.setPosition(0, 640);

    satsanaAnimation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, true);
}

void Cutscene::draw()
{
	this->app->clear();
	this->app->draw(background);
	this->app->draw(mainCharacter);
	this->app->draw(otherCharacter);
	this->app->draw(dialogueBox);
	this->app->draw(scoreText);
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
	satsanaAnimation->animate(dt, app);
	this->app->display();

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
		dialogueStr = "Current score is "+ std::to_string(this->score)+ ".\nPress [SPACE BAR] to skip.";
		background.setTexture(backgroundTexture);
		mainCharacter.setTexture(mcTexture);
		otherCharacter.setTexture(otherCharacterTexture);
		dialogueBox.setTexture(dialogueBoxTexture);
		otherCharacter.setPosition(800,0);
		dialogueBox.setPosition(0, 600);
		scoreText.setPosition(125, 625);
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