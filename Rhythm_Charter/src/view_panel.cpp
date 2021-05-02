#include "view_panel.h"

View_Panel::View_Panel(sf::Vector2f panelPos, sf::Vector2f panelDim, sf::Vector2f sliderPos, TYPE type) : GUI_Element(type)
{
  //
  this->panel.setPosition(panelPos);
  this->panel.setSize(panelDim);
	//this->panel.setOrigin(panelDim / 2.0f);
	this->panel.setFillColor(sf::Color::White);

	/*
	/ Slider in the scrollbar
	*/
	this->slider.setSize(panelDim / 10.f);
	this->slider.setPosition(sliderPos.x + panelDim.x / 20.f, sliderPos.y + 800.0f * 0.01f);
	this->slider.setOrigin(this->slider.getSize() /2.f);
	this->slider.setFillColor(sf::Color(245,245,245,64));
}

bool View_Panel::selected(sf::Vector2f mousePos) {

}

void View_Panel::autoScroll(std::shared_ptr<Music_Player> music_player, )
{
  //Middle area
  if((this->WINDOW_SIZE.x - 32.0f) * music_player->getRatio() + this->slider.getSize().x < this->WINDOW_SIZE.x &&
      (this->WINDOW_SIZE.x - 32.0f) * music_player->getRatio() - this->slider.getSize().x/2.f > 0)
	 this->slider.setPosition((this->WINDOW_SIZE.x - 32.0f) * music_player->getRatio(), this->WINDOW_SIZE.y - 120.0f + this->slider.getSize().y/8.0f);
   //Left end
  else if ((this->WINDOW_SIZE.x - 32.0f) * music_player->getRatio() - this->slider.getSize().x/2.f < 0) {
    this->slider.setPosition(this->slider.getSize().x / 2.f, this->WINDOW_SIZE.y - 120.0f + this->slider.getSize().y/8.0f);
    //Right End
  } else {
    this->slider.setPosition((this->WINDOW_SIZE.x - 32.0f) - this->slider.getSize().x / 4.f, this->WINDOW_SIZE.y - 120.0f + this->slider.getSize().y/8.0f);
  }
}
void View_Panel::draw(std::shared_ptr<sf::RenderWindow> window) {
  window->draw(this->panel);
	window->draw(this->slider);
}
