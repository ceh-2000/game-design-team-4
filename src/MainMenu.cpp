#include "MainMenu.h"
#include <array>
#include <string>

MainMenu::MainMenu(std::shared_ptr<sf::RenderWindow> app) {
    this->app = app;

    selectedItemIndex = 0;
    chefNameString= "";
    finalChef = finalChefs[0];

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

    returnBack.setFont(this->font);
    returnBack.setCharacterSize(36);
    returnBack.setPosition(20, 690);
    returnBack.setStyle(sf::Text::Bold);
    returnBack.setString("Press escape to return to menu");

    settingsTitle.setFont(this->font);
    settingsTitle.setCharacterSize(64);
    settingsTitle.setPosition(480, 20);
    settingsTitle.setString("SETTINGS");

    settingsOptions[0].setFont(this->font);
    settingsOptions[0].setCharacterSize(48);
    settingsOptions[0].setPosition(20, 150);
    settingsOptions[0].setString("Enter Chef Name: " + chefNameString);
    settingsOptions[0].setFillColor(sf::Color::Green);

    settingsOptions[1].setFont(this->font);
    settingsOptions[1].setCharacterSize(48);
    settingsOptions[1].setPosition(20, 350);
    settingsOptions[1].setString("Select Final Chef: " + finalChef);
    settingsOptions[1].setFillColor(sf::Color::White);


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
    if(currentScreen == 0){
        if(selectedItemIndex < 2){
            options[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex += 1;
            options[selectedItemIndex].setFillColor(sf::Color::Green);
        }
    }
    else if(currentScreen == 1){
        if(optionsSelected < 1){
            settingsOptions[optionsSelected].setFillColor(sf::Color::White);
            optionsSelected += 1;
            settingsOptions[optionsSelected].setFillColor(sf::Color::Green);
        }
    }
}

void MainMenu::moveUp(){
    if(currentScreen == 0){
        if(selectedItemIndex > 0){
            options[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex -= 1;
            options[selectedItemIndex].setFillColor(sf::Color::Green);
        }
    }
    else if(currentScreen == 1){
        if(optionsSelected > 0){
            settingsOptions[optionsSelected].setFillColor(sf::Color::White);
            optionsSelected -= 1;
            settingsOptions[optionsSelected].setFillColor(sf::Color::Green);
        }
    }
}

void MainMenu::selectLeft(){
    if(currentScreen == 1 && optionsSelected == 1){
        if(chefSelected > 0){
            chefSelected -= 1;
            finalChef = finalChefs[chefSelected];
        }
    }
}

void MainMenu::selectRight(){
    if(currentScreen == 1 && optionsSelected == 1){
        if(chefSelected < 2){
            chefSelected += 1;
            finalChef = finalChefs[chefSelected];
        }
    }
}

int MainMenu::chooseSelection(){
    return(selectedItemIndex);
}

void MainMenu::drawOptions(const float& deltaTime){
    this->app->clear(sf::Color(193, 148, 126));

    this->app->draw(returnBack);
    this->app->draw(settingsTitle);
    settingsOptions[0].setString("Enter Chef Name: " + chefNameString);
    this->app->draw(settingsOptions[0]);
    settingsOptions[1].setString("Select Final Chef: " + finalChef);
    this->app->draw(settingsOptions[1]);

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

    std::string works = "ART:\n"
                        "Conveyor belt sprite sheet: https://opengameart.org/content/isometric-conveyor-belt-animation\n"
                         "Sushi sprite: https://www.freepik.com/premium-vector/pixel-art-japanese-food-sushi-bit-game-item_11812806.html\n"
                         "Pizza sprite: https://www.pinterest.com/pin/369717450659483649/\n"
                         "All other assets were created by our team"
                         "\n\n"
                         "MUSIC:\n";

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

void MainMenu::addTextToName(sf::String newInput){
    if(chefNameString.getSize() < 20){
        chefNameString += newInput;
        settingsOptions[0].setString("Enter Chef Name: " + chefNameString);
    }
}