#include "CutScene.h"

CutScene::CutScene(std::shared_ptr<sf::RenderWindow> app) {
    this->app = app;

    if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }
    this->sceneText.setFont(font);
    this->sceneText.setCharacterSize(50);
    this->sceneText.setFillColor(sf::Color::Red);
}

void CutScene::draw(const float &dt){
    this->app->clear(sf::Color::Cyan);
    this->sceneText.setString("Current score is "+std::to_string(this->score)+".\nPress SPACE BAR to skip.");
    this->app->draw(sceneText);
    this->app->display();
}