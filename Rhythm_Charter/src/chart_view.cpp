#include "chart_view.h"
#include <iostream>

Chart_View::Chart_View(std::shared_ptr<Chart_Logic> chart_logic)
{
	this->chart_logic = chart_logic;

	// this->music_player = std::make_shared<Music_Player>(or a list of strings);
	this->music_player = std::make_shared<Music_Player>("../data/music/Gettin' Freaky (Main Menu) - Friday Night Funkin' OST-HQ.ogg");
	// this->music_player = std::make_shared<Music_Player>("../data/music/Milf_Inst.ogg");
	// this->music_player = std::make_shared<Music_Player>("../data/music/Death Grips - Exmilitary - 3 - Spread Eagle Cross the Block.wav");
	this->WINDOW_SIZE = this->chart_logic->getWindowSize();
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(this->WINDOW_SIZE.x,this->WINDOW_SIZE.y,32), "Rhythm Charter", sf::Style::Default);
	this->GUIList = this->chart_logic->getGUIList();

	this->font.loadFromFile("../data/fonts/orange kid.ttf");
	// this->fileText = sf::Text("", font, 30);	
	this->text = sf::Text("", this->font, 30);
	this->text.setPosition(sf::Vector2f(this->WINDOW_SIZE.x/1.5f, this->WINDOW_SIZE.y - 64.0f - this->text.getCharacterSize()/2.0f));

	this->demoChart();
}

void Chart_View::pollInput()
{
	sf::Event event;
		while (window->pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					this->chart_logic->setActive(false);
					break;

				case sf::Event::Resized:
					this->WINDOW_SIZE.x = event.size.width;
					this->WINDOW_SIZE.y = event.size.height;
					break;

				case sf::Event::KeyPressed:

					if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)))
					{
						//reverse change
						//this->chart->getTimings().pop_back();
						//this->chart->getBeats().pop_back();d
					}

					switch(event.key.code)
					{
						case sf::Keyboard::Q:
						case sf::Keyboard::Escape:
							this->chart_logic->setActive(false);
							break;

						case sf::Keyboard::P:
							this->music_player->pause();
							break;

						case sf::Keyboard::Up:
						case sf::Keyboard::W:
							this->music_player->increaseVolume(5);
							break;

						case sf::Keyboard::Down:
						case sf::Keyboard::S:
							this->music_player->decreaseVolume(5);
							break;

						case sf::Keyboard::Left:
						case sf::Keyboard::A:
							this->music_player->decrementPos(5);
							break;

						case sf::Keyboard::Right:
						case sf::Keyboard::D:
							this->music_player->incrementPos(5);
							break;

						case sf::Keyboard::C:
							this->chart_music();
							break;

						case sf::Keyboard::L:
							// this->chart_logic->getChart->importInput();
							break;

						case sf::Event::TextEntered:
							// if(this->textfield->getOutlineColor() == sf::Color::Blue)
							// this->filePath += event.text.unicode;
							break;
					}

					case sf::Event::MouseButtonPressed:

						pixelPos = sf::Mouse::getPosition(*this->window);
						worldPos = this->window->mapPixelToCoords(pixelPos);
						if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							// this->music_player->play();
							int counter = 0;
							for(auto itr = this->GUIList.begin(); itr< this->GUIList.begin()+3; ++itr)
								if((*itr)->selected(worldPos))
								switch(counter)
								{
									case 0:
										if(!this->music_player->isPlaying())
											this->music_player->play();
										else
											this->music_player->pause();
									break;
									case 1:
										this->music_player->stop();
									break;
									case 2:
										this->chart_music();
									break;
								}
								counter++;
							for(auto itr = this->GUIList.begin()+3; itr < this->GUIList.end(); ++itr)
								(*itr)->selected(worldPos);
						}
						// this->chart_logic->getChart->selected(this->worldPos);

						// else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
						// {
						// 	// this->chart_logic->getChart->selected(this->worldPos);
						// }
						break;
		}
	}
}

void Chart_View::demoChart()
{
	int counter = 0;
	for(float i = 0; i < this->music_player->getDuration(); i++)
	{
		counter++;
		if(counter%6 == 0)
			this->chart_logic->getChart()->addInput(16.0f + 16.0f*i, this->WINDOW_SIZE.y, counter);
	}
	this->chart_logic->getChart()->saveJSON();
}


void Chart_View::chart_music()
{
	this->chart_logic->getChart()->addInput(this->chart_logic->getScrollBar()->getSliderPos().x, this->WINDOW_SIZE.y, this->music_player->getPlayTime());
}


void Chart_View::draw()
{
	this->window->clear();
	for(auto element : this->GUIList)
		element->draw(this->window);
	this->window->draw(text);
	this->window->display();
}

void Chart_View::update()
{
	this->chart_logic->getScrollBar()->autoScroll(this->music_player);
	this->text.setString(this->music_player->getText());
	this->music_player->updateText();
	pollInput();
	draw();
}