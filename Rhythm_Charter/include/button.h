#ifndef BUTTON_H
#define BUTTON_H
#include "gui_element.h"
/*/////
// Button class, checks if clicked or not
*//////
class Button : public GUI_Element
{
private:
	std::string imgPath = "../data/art/buttons-spritesheet.png";
	sf::RectangleShape buttonShape;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect rectSourceSprite;
	bool isClicked = false;

public:
	Button(sf::Vector2f pos, sf::Vector2f dim, TYPE type, int row=-1);
	bool selected(sf::Vector2f mousePos);
	void draw(std::shared_ptr<sf::RenderWindow> window);
};
#endif