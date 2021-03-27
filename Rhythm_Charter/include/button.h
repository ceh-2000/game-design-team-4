#ifndef BUTTON_H
#define BUTTON_H
#include "gui_element.h"
/*/////
// Button class, checks if clicked or not
*//////
class Button : public GUI_Element
{
private:
	sf::RectangleShape buttonShape;
	sf::Sprite sprite;
	sf::Texture texture;
	bool isClicked = false;

public:
	Button(sf::Vector2f pos, sf::Vector2f dim, std::string imgPath, TYPE type);
	bool selected(sf::Vector2f mousePos);
	void draw(std::shared_ptr<sf::RenderWindow> window);
};
#endif