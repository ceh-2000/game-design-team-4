#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<sf::RenderWindow> app) {
    this->app = app;

    if (!this->font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }

    this->sceneText.setFont(this->font);
    this->sceneText.setCharacterSize(50);
    this->sceneText.setFillColor(sf::Color::White);
}

void MainMenu::draw(const float &dt){
    this->app->clear(sf::Color::Magenta);
    this->sceneText.setString("Main Menu\nPress SPACE BAR to start game.");
    this->app->draw(this->sceneText);
    this->app->display();
}
