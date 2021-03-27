#include "chart_view.h"
#include <iostream>

Chart_View::Chart_View(std::shared_ptr<Chart_Logic> chart_logic)
{
	this->chart_logic = chart_logic;
	this->music_player = this->chart_logic->getMusic();
	this->horiz_scrollbar = this->chart_logic->getScrollBar();
	this->input_chart = this->chart_logic->getChart();

	this->WINDOW_SIZE = this->chart_logic->getWindowSize();
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(this->WINDOW_SIZE.x,this->WINDOW_SIZE.y,32), "Rhythm Charter", sf::Style::Default);
	this->GUIList = this->chart_logic->getGUIList();
	this->font.loadFromFile("../data/fonts/orange kid.ttf");
	this->text = sf::Text("", this->font, 30);
	this->text.setPosition(sf::Vector2f(this->WINDOW_SIZE.x/1.5f, this->WINDOW_SIZE.y - 64.0f - this->text.getCharacterSize()/2.0f));
	this->volume = sf::Text(this->music_player->getVolume(), this->font, 30);
	this->volume.setPosition(sf::Vector2f(this->WINDOW_SIZE.x + 16.0f, this->WINDOW_SIZE.y/2.0f));
	this->volume.setOrigin(sf::Vector2f(((this->WINDOW_SIZE.x + 16.0f)/2.0f), this->WINDOW_SIZE.y/4.0f));

	// this->demoChart();
}

void Chart_View::pollInput()
{
	sf::Event event;
		while (window->pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:	this->chart_logic->setActive(false); break;

				case sf::Event::Resized:
					this->WINDOW_SIZE.x = event.size.width;
					this->WINDOW_SIZE.y = event.size.height;
					break;

				case sf::Event::KeyPressed:

					switch(event.key.code)
					{
						case sf::Keyboard::Q:
						case sf::Keyboard::Escape: this->chart_logic->setActive(false); break;

						case sf::Keyboard::P: this->music_player->pause(); break;

						case sf::Keyboard::Up:
						case sf::Keyboard::W: this->music_player->increaseVolume(5); break;

						case sf::Keyboard::Down:
						case sf::Keyboard::S: this->music_player->decreaseVolume(5); break;

						case sf::Keyboard::Left:
						case sf::Keyboard::A: this->music_player->decrementPos(5); break;

						case sf::Keyboard::Right:
						case sf::Keyboard::D: this->music_player->incrementPos(5); break;

						case sf::Keyboard::C: this->chart_music(); break;

						case sf::Keyboard::Delete: this->input_chart->delInput(); break;
						
						case sf::Keyboard::L: // this->chart_logic->getChart->importInput();
							break;
						case sf::Event::TextEntered:
							
							// if(this->textfield->getOutlineColor() == sf::Color::Blue)
							this->filePath += event.text.unicode;
							break;
					}

					case sf::Event::MouseButtonPressed:

						pixelPos = sf::Mouse::getPosition(*this->window);
						worldPos = this->window->mapPixelToCoords(this->pixelPos);
						if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							for(auto itr = this->GUIList.begin(); itr < this->GUIList.end(); ++itr)
							{
								if((*itr)->selected(worldPos))
								{
									switch((*itr)->getType())
									{
										case TYPE::PLAY_BTN:
											if(!this->music_player->isPlaying()) this->music_player->play();
											else this->music_player->pause();
										break;

										case TYPE::STOP_BTN: this->music_player->stop(); break;
										case TYPE::CHART_BTN: this->chart_music(); break;

										case TYPE::TEXTFIELD:
											this->input_chart->saveJSON();
										break;
									}
								}
							}
						}
					break;

					case sf::Event::MouseButtonReleased:
						this->startPos = sf::Mouse::getPosition(*this->window);
						this->endPos = this->window->mapPixelToCoords(this->startPos);

						//bound the mouseReleased coords
						if(endPos.x < this->horiz_scrollbar->getBar().getPosition().x)
							endPos.x = this->horiz_scrollbar->getBar().getPosition().x;
						else if (endPos.x > this->horiz_scrollbar->getBar().getPosition().x + this->horiz_scrollbar->getBar().getSize().x)
							endPos.x = this->horiz_scrollbar->getBar().getPosition().x + this->horiz_scrollbar->getBar().getSize().x;
						this->input_chart->moveInput(this->endPos, this->horiz_scrollbar->getBar().getPosition().x + this->horiz_scrollbar->getBar().getSize().x);
					break;
					default:
					break;
		}
	}
}

void Chart_View::demoChart()
{
	int counter = 0;
	for(float i = 0; i < this->music_player->getDuration(); i+=0.5172413793103448f)
		this->input_chart->addInput(this->horiz_scrollbar->getBar().getSize().x *
		i/this->music_player->getDuration() + this->horiz_scrollbar->getBar().getSize().x, this->WINDOW_SIZE.y, i, this->font);
	this->input_chart->saveJSON();
}

void Chart_View::chart_music()
{
	this->input_chart->addInput(this->horiz_scrollbar->getSlider().getPosition().x, this->WINDOW_SIZE.y, this->music_player->getPlayTime(), this->font);
}

void Chart_View::draw()
{
	this->window->clear();
	for(auto element : this->GUIList)
		element->draw(this->window);
	this->window->draw(this->volume);
	this->window->draw(this->text);
	this->window->display();
}

void Chart_View::update()
{
	this->horiz_scrollbar->autoScroll(this->music_player);
	this->text.setString(this->music_player->getText());
	this->music_player->updateText();
	pollInput();
	draw();
}