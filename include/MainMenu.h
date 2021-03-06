#ifndef CSCI437_MAINMENU_H
#define CSCI437_MAINMENU_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <array>

class MainMenu {
private:
    std::shared_ptr<sf::RenderWindow> app;
    sf::Font font;
    sf::Font font1;

    sf::Texture conceptArt;
    sf::Sprite conceptArtSprite;

    sf::Text startGame;
    sf::Text settings;
    sf::Text gameTitle;
    sf::Text resources;
    sf::Text returnBack;
    sf::Text settingsTitle;
    sf::Text mainMenuInstr;
    sf::Text chefNameInstr;
    sf::Text finalChefInstr;

    sf::Vector2f startGamePos;
    sf::Vector2f settingsPos;
    sf::Vector2f gameTitlePos;
    sf::Vector2f resourcesPos;
    sf::Vector2f gameLogoPos;
    sf::Vector2f conceptArtPos;
    sf::Vector2f mainMenuInstrPos;
    sf::Vector2f chefNameInstrPos;
    sf::Vector2f finalChefInstrPos;


    sf::Texture gameLogo;
    sf::Sprite logoSprite;

    int selectedItemIndex;

    int currentScreen = 0;

    std::array<sf::Text, 3> options = {startGame, settings, resources};

    sf::String chefNameString;
    sf::Text chefName;
    sf::Text finalChefSetting;

    std::array<sf::Text, 2> settingsOptions = {chefName, finalChefSetting};
    int optionsSelected = 0;

    std::array<sf::String, 3> finalChefs = {sf::String("Guy Fieri"), sf::String("Bobby Flay"), sf::String("Gordon Ramsay")};
    int chefSelected;
    sf::String finalChef;

public:
    MainMenu(std::shared_ptr<sf::RenderWindow> app);

    void draw(const float &dt, int screen);

    sf::Vector2f getSelectionBox();
    void setSelectionBox(sf::Vector2f position);

    sf::Vector2f getStartGamePos(){ return startGamePos; }
    sf::Vector2f getSettingsPos(){ return settingsPos; }
    sf::Vector2f getResourcesPos(){ return resourcesPos; }

    void moveUp();
    void moveDown();

    int chooseSelection();

    void drawOptions(const float& deltaTime);
    void drawResources(const float& deltaTime);

    int getCurrentScreen(){ return currentScreen; }
    void setCurrentScreen(int screen){ currentScreen = screen; }

    int getOptionSelected(){ return optionsSelected; }

    void addTextToName(sf::String newInput);

    sf::String &getUserChefName(){ return chefNameString; }
    void setUserChefName(sf::String newName){ chefNameString = newName;}

    void selectLeft();
    void selectRight();

    sf::String &getFinalChef(){ return finalChef; }
};

#endif //CSCI437_MAINMENU_H
