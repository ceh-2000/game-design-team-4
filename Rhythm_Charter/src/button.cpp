#include "button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f dim, TYPE type, int row) : GUI_Element(type)
{
	if(row != -1)
	{
		this->texture.loadFromFile(this->imgPath);
		this->rectSourceSprite = sf::IntRect(sf::Vector2i(0, dim.y*row), sf::Vector2i(dim));
		this->sprite = sf::Sprite(this->texture, this->rectSourceSprite);
		this->sprite.setPosition(pos);
		this->sprite.setOrigin(dim/2.0f);
	}
		this->buttonShape.setPosition(pos);
		this->buttonShape.setSize(dim);
		this->buttonShape.setOrigin(dim/2.0f);
		this->buttonShape.setFillColor(sf::Color::White);
}

bool Button::selected(sf::Vector2f mousePos)
{
	if (mousePos.x >= this->buttonShape.getPosition().x
	&& mousePos.x <= this->buttonShape.getPosition().x + this->buttonShape.getSize().x
	&& mousePos.y >= this->buttonShape.getPosition().y
	&& mousePos.y <= this->buttonShape.getPosition().y + this->buttonShape.getSize().y)
		{
			if(this->rectSourceSprite.left == 32)
				this->rectSourceSprite.left-=32;
			else
				this->rectSourceSprite.left+=32;

			if(this->isClicked) this->isClicked = false;
			else this->isClicked = true; 
			this->sprite.setTextureRect(this->rectSourceSprite);
			return true;
		}
	return false;
}

void Button::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(this->buttonShape);
	window->draw(this->sprite);
}