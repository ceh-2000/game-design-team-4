#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream> //for debugging

/*//////////////////////////
// Super class for gui objects (button, horizontal scrollbar, input_chart)
*///////////////////////////
enum class TYPE { PLAY_BTN, STOP_BTN, CHART_BTN, TEXTFIELD, SCROLLBAR, INPUT_CHART};
class GUI_Element : std::enable_shared_from_this<GUI_Element>
{
private:
    TYPE type;
public:
    GUI_Element(TYPE type);
    virtual void draw(std::shared_ptr<sf::RenderWindow> window) = 0;
    virtual bool selected(sf::Vector2f mousePos) = 0;
    TYPE getType() { return this->type;}
    void setType(TYPE &type) { this->type = type; }
};
#endif