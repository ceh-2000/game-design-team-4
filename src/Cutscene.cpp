#include "Cutscene.h"

Cutscene::Cutscene(std::shared_ptr<sf::RenderWindow> app)
{
    this->app = app;
    // dialogueBox = sf::Sprite(dialogueBoxTexture, sf::IntRect(0,0,1200,200));
}

void Cutscene::draw()
{
    app->clear(sf::Color::Black);
    app->draw(background);
    app->draw(mainCharacter);
    app->draw(otherCharacter);
    // app->draw(dialogueBox);
}

void Cutscene::update(const float& dt)
{
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
        background = sf::Sprite(backgroundTexture, sf::IntRect(0,0,1200,800));
        mainCharacter = sf::Sprite(mcTexture, sf::IntRect(0,0,500,800));
        otherCharacter = sf::Sprite(otherCharacterTexture, sf::IntRect(0,0,1200,800));
        otherCharacter.setPosition(500,0);
    break;
    default: break;
    }
}