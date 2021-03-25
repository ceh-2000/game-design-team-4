#include "horizontal_scrollbar.h"



Horizontal_Scrollbar::Horizontal_Scrollbar(sf::Vector2f pos, sf::Vector2f dim) : GUI_Element()
{
	this->bar.setPosition(pos);
	this->bar.setOrigin(this->slider.getSize() / 2.0f);
	this->bar.setSize(dim);
	this->bar.setFillColor(sf::Color(211,211,211,32));

	/*
	/ Slider in the scrollbar
	*/
	this->slider.setSize(sf::Vector2f(dim.y, dim.y));
	this->slider.setPosition(pos.x, pos.y + dim.y / 2.0f);
	this->slider.setOrigin(this->slider.getSize() / 2.0f);
	this->slider.setFillColor(sf::Color::White);
}


bool Horizontal_Scrollbar::selected(sf::Vector2f mousePos)
{
	if (this->bar.getOrigin().x <= mousePos.x && this->bar.getOrigin().y <= mousePos.y
	&& mousePos.x <= this->bar.getSize().x && mousePos.y <= this->bar.getSize().y)
		this->slider.setPosition(sf::Vector2f(mousePos.x, this->slider.getPosition().y));
}


void Horizontal_Scrollbar::autoScroll(std::shared_ptr<Music_Player> music_player)
{
	this->slider.setPosition(this->bar.getSize().x * music_player->getRatio() + this->slider.getSize().x, this->bar.getPosition().y + this->slider.getSize().y/2.0f);
}


void Horizontal_Scrollbar::draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(this->bar);
	window->draw(this->slider);
}