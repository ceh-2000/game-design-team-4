#ifndef BUTTON_H
#define BUTTON_H

#include "gui_element.h"

class Button : public GUI_Element
{
private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;

    sf::Vector2i pixelPos;
    sf::Vector2f worldPos;

    bool isClicked = false;
    
public:
    Button(sf::Vector2f pos, sf::Vector2f dim, sf::Text text, sf::Color fill);
    bool clicked(std::shared_ptr<sf::RenderWindow> window);
    void draw(std::shared_ptr<sf::RenderWindow> window);
};

#endif