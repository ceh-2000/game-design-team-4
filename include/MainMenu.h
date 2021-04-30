#ifndef CSCI437_MAINMENU_H
#define CSCI437_MAINMENU_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

class MainMenu {
private:
    std::shared_ptr<sf::RenderWindow> app;
    sf::Font font;
    sf::Font font1;

    sf::Text startGame;
    sf::Text settings;
    sf::Text gameTitle;
    sf::Text resources;

    sf::Vector2f startGamePos;
    sf::Vector2f settingsPos;
    sf::Vector2f gameTitlePos;
    sf::Vector2f resourcesPos;
    sf::Vector2f gameLogoPos;

    sf::Texture gameLogo;
    sf::Sprite logoSprite;

    int selectedItemIndex;

public:
    MainMenu(std::shared_ptr<sf::RenderWindow> app);

    void draw(const float &dt);

    sf::Vector2f getSelectionBox();
    void setSelectionBox(sf::Vector2f position);

    sf::Vector2f getStartGamePos(){ return startGamePos; }
    sf::Vector2f getSettingsPos(){ return settingsPos; }
    sf::Vector2f getResourcesPos(){ return resourcesPos; }

    void moveUp();
    void moveDown();
};

#endif //CSCI437_MAINMENU_H
