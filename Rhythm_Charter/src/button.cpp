#include "button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f dim, std::string imgPath, TYPE type) : GUI_Element(type)
{
	this->buttonShape.setPosition(pos);
	this->buttonShape.setSize(dim);
	this->buttonShape.setOrigin(dim/2.0f);
	this->buttonShape.setFillColor(sf::Color::White);
	// this->type = imgPath;
}

bool Button::selected(sf::Vector2f mousePos)
{
	if (mousePos.x >= this->buttonShape.getPosition().x
	&& mousePos.x <= this->buttonShape.getPosition().x + this->buttonShape.getSize().x
	&& mousePos.y >= this->buttonShape.getPosition().y
	&& mousePos.y <= this->buttonShape.getPosition().y + this->buttonShape.getSize().y)
		{
			if(this->isClicked) this->isClicked = false;
			else this->isClicked = true;
			return true;
		}
	return false;
}

void Button::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(this->buttonShape);
}