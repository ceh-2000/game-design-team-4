#include "button.h"
#include <iostream>

Button::Button(sf::Vector2f pos, sf::Vector2f dim, sf::Color fill) : GUI_Element()
{
	this->buttonShape.setPosition(pos);
	this->buttonShape.setSize(dim);
	this->buttonShape.setOrigin(dim/2.0f);
	this->buttonShape.setFillColor(fill);
}

bool Button::selected(sf::Vector2f mousePos)
{
	if (mousePos.x >= this->buttonShape.getPosition().x
	&& mousePos.x <= this->buttonShape.getPosition().x + this->buttonShape.getSize().x
	&& mousePos.y >= this->buttonShape.getPosition().y
	&& mousePos.y <= this->buttonShape.getPosition().y + this->buttonShape.getSize().y)
		{
			if(this->isClicked){this->isClicked = false;}
			else{this->isClicked = true;}
			return true;
		}
	return false;
}

void Button::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(this->buttonShape);
}