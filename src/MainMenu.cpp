#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<sf::RenderWindow> app) {
    this->app = app;

    selectedItemIndex = 0;

    this->startGamePos = sf::Vector2f(20, 250);
    this->settingsPos = sf::Vector2f(20, 450);
    this->resourcesPos = sf::Vector2f(20, 650);
    this->gameTitlePos = sf::Vector2f(335, 30);
    this->gameLogoPos = sf::Vector2f(400, 250);

    if (!this->font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }

    if (!this->gameLogo.loadFromFile("../data/art/game-logo.png")) {
        std::cout << "Could not load game-logo.png" << std::endl;
    }

    this->startGame.setFont(this->font);
    this->startGame.setCharacterSize(64);
    this->startGame.setFillColor(sf::Color::White);
    this->startGame.setStyle(sf::Text::Bold);
    this->startGame.setPosition(startGamePos);
    this->startGame.setString("PLAY GAME");

    this->settings.setFont(this->font);
    this->settings.setCharacterSize(64);
    this->settings.setFillColor(sf::Color::White);
    this->settings.setStyle(sf::Text::Bold);
    this->settings.setPosition(settingsPos);
    this->settings.setString("SETTINGS");

    this->resources.setFont(this->font);
    this->resources.setCharacterSize(64);
    this->resources.setFillColor(sf::Color::White);
    this->resources.setStyle(sf::Text::Bold);
    this->resources.setPosition(resourcesPos);
    this->resources.setString("RESOURCES");

    this->gameTitle.setFont(this->font);
    this->gameTitle.setCharacterSize(128);
    this->gameTitle.setFillColor(sf::Color::White);
    this->gameTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
    this->gameTitle.setPosition(gameTitlePos);
    this->gameTitle.setString("WELCOME TO");

    this->logoSprite.setTexture(this->gameLogo);
    this->logoSprite.setPosition(gameLogoPos);
    this->logoSprite.setScale(sf::Vector2f(2.0, 2.0));

    
}

void MainMenu::draw(const float &dt){
    this->app->clear(sf::Color::Magenta);

    this->app->draw(this->startGame);
    this->app->draw(this->settings);
    this->app->draw(this->resources);
    this->app->draw(this->gameTitle);
    this->app->draw(this->logoSprite);

    this->app->display();
}

void MainMenu::moveUp(){
    selectedItemIndex += 1;
}

void MainMenu::moveDown(){
    selectedItemIndex -= 1;
}
