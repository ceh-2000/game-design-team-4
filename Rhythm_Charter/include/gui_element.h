#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <SFML/Graphics.hpp>
#include <memory>

/*//////////////////////////
// Super class for gui objects (button, horizontal scrollbar, input_chart)
*///////////////////////////
class GUI_Element : std::enable_shared_from_this<GUI_Element>
{
private:
public:
    GUI_Element(){}
    virtual void draw(std::shared_ptr<sf::RenderWindow> window) = 0;
    virtual bool selected(sf::Vector2f mousePos) = 0;
};

#endif