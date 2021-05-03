#include "MainMenu.h"
#include <array>
#include <string>

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

    options[0].setFont(this->font);
    options[0].setCharacterSize(64);
    options[0].setFillColor(sf::Color::Green);
    options[0].setStyle(sf::Text::Bold);
    options[0].setPosition(startGamePos);
    options[0].setString("PLAY GAME");

    options[1].setFont(this->font);
    options[1].setCharacterSize(64);
    options[1].setFillColor(sf::Color::White);
    options[1].setStyle(sf::Text::Bold);
    options[1].setPosition(settingsPos);
    options[1].setString("SETTINGS");

    options[2].setFont(this->font);
    options[2].setCharacterSize(64);
    options[2].setFillColor(sf::Color::White);
    options[2].setStyle(sf::Text::Bold);
    options[2].setPosition(resourcesPos);
    options[2].setString("RESOURCES");

    this->gameTitle.setFont(this->font);
    this->gameTitle.setCharacterSize(128);
    this->gameTitle.setFillColor(sf::Color::White);
    this->gameTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
    this->gameTitle.setPosition(gameTitlePos);
    this->gameTitle.setString("WELCOME TO");

    this->logoSprite.setTexture(this->gameLogo);
    this->logoSprite.setPosition(gameLogoPos);
    this->logoSprite.setScale(sf::Vector2f(2.0, 2.0));

    //options = {this->startGame, this->settings, this->resources};

    
}

void MainMenu::draw(const float &dt, int screen){

    //main menu
    if(screen == 0){
        this->app->clear(sf::Color(193, 148, 126));

        this->app->draw(options[0]);
        this->app->draw(options[1]);
        this->app->draw(options[2]);
        this->app->draw(this->gameTitle);
        this->app->draw(this->logoSprite);

        this->app->display();
    }

    //settings
    else if(screen == 1){
        drawOptions(dt);
    }

    //resources
    else if(screen == 2){
        drawResources(dt);
    }
}

void MainMenu::moveDown(){
    options[selectedItemIndex % options.size()].setFillColor(sf::Color::White);
    selectedItemIndex += 1;
    options[selectedItemIndex % options.size()].setFillColor(sf::Color::Green);
}

void MainMenu::moveUp(){
    options[selectedItemIndex % options.size()].setFillColor(sf::Color::White);
    selectedItemIndex -= 1;
    options[selectedItemIndex % options.size()].setFillColor(sf::Color::Green);
}

int MainMenu::chooseSelection(){
    return(selectedItemIndex);
}

void MainMenu::drawOptions(const float& deltaTime){
    this->app->clear(sf::Color(193, 148, 126));

    sf::Text returnBack;
    returnBack.setFont(this->font);
    returnBack.setCharacterSize(36);
    returnBack.setPosition(20, 690);
    returnBack.setStyle(sf::Text::Bold);
    returnBack.setString("Press escape to return to menu");

    sf::Text settingsTitle;
    settingsTitle.setFont(this->font);
    settingsTitle.setCharacterSize(64);
    settingsTitle.setPosition(480, 20);
    settingsTitle.setString("SETTINGS");

    this->app->draw(returnBack);
    this->app->draw(settingsTitle);
    this->app->display();
}

void MainMenu::drawResources(const float& deltaTime){
    this->app->clear(sf::Color(193, 148, 126));

    sf::Text returnBack;
    returnBack.setFont(this->font);
    returnBack.setCharacterSize(36);
    returnBack.setPosition(20, 690);
    returnBack.setStyle(sf::Text::Bold);
    returnBack.setString("Press escape to return to menu");

    std::string works = "Conveyor belt sprite sheet: https://opengameart.org/content/isometric-conveyor-belt-animation\n"
                         "Sushi sprite: https://www.freepik.com/premium-vector/pixel-art-japanese-food-sushi-bit-game-item_11812806.html\n"
                         "Pizza sprite: https://www.pinterest.com/pin/369717450659483649/\n"
                         "All other assets were created by our team";

    sf::Text worksCited;
    worksCited.setFont(this->font);
    worksCited.setCharacterSize(30);
    worksCited.setPosition(20, 100);
    worksCited.setString(works);

    sf::Text resourcesTitle;
    resourcesTitle.setFont(this->font);
    resourcesTitle.setCharacterSize(64);
    resourcesTitle.setPosition(450, 20);
    resourcesTitle.setString("RESOURCES");

    this->app->draw(returnBack);
    this->app->draw(worksCited);
    this->app->draw(resourcesTitle);
    this->app->display();
}