#include "button.h"
#include <iostream>

Button::Button(sf::Vector2f pos, sf::Vector2f dim, sf::Text text, sf::Color fill) : GUI_Element()
{
	this->buttonShape.setPosition(pos);
	this->buttonShape.setSize(dim);
	this->buttonShape.setOrigin(dim/2.0f);
	this->buttonShape.setFillColor(fill);

	this->buttonText.setPosition(pos-dim/2.0f);
	this->buttonText.setOrigin((pos-dim/2.0f)/2.0f);
}

bool Button::clicked(std::shared_ptr<sf::RenderWindow> window)
{
	this->pixelPos = sf::Mouse::getPosition(*window);
	this->worldPos = window->mapPixelToCoords(this->pixelPos);

	if (this->worldPos.x >= this->buttonShape.getPosition().x
	&& this->worldPos.x <= this->buttonShape.getPosition().x + this->buttonShape.getSize().x
	&& this->worldPos.y >= this->buttonShape.getPosition().y
	&& this->worldPos.y <= this->buttonShape.getPosition().y + this->buttonShape.getSize().y)
		{
			if(this->isClicked){this->isClicked = false;}
			else{this->isClicked = true;}
			std::cout << " clicked " << std::endl;
			return true;
		}
	return false;
}

void Button::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(this->buttonShape);
}