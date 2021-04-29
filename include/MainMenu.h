#ifndef CSCI437_MAINMENU_H
#define CSCI437_MAINMENU_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

class MainMenu {
private:
    std::shared_ptr<sf::RenderWindow> app;
    sf::Font font;
    sf::Text sceneText;

public:
    MainMenu(std::shared_ptr<sf::RenderWindow> app);

    void draw(const float &dt);
};

#endif //CSCI437_MAINMENU_H
