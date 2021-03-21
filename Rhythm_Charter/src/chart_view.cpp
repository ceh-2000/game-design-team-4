#include "chart_view.h"
#include <iostream>

Chart_View::Chart_View(std::shared_ptr<Chart_Logic> chart_logic)
{
    this->chart_logic = chart_logic;    
    this->WINDOW_SIZE = this->chart_logic->getWindowSize();
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(this->WINDOW_SIZE.x,this->WINDOW_SIZE.y,32), "Rhythm Charter", sf::Style::Default);
    init();
    this->demoChart();

}

void Chart_View::init()
{
    // this->music_player = std::make_shared<Music_Player>(or a list of strings);

	this->music_player = std::make_shared<Music_Player>("../data/music/Philly Nice - Friday Night Funkin' OST-HQ.ogg");

    // this->music_player = std::make_shared<Music_Player>("../data/music/Milf_Inst.ogg");
	// this->music_player = std::make_shared<Music_Player>("../data/music/Death Grips - Exmilitary - 3 - Spread Eagle Cross the Block.wav");

	this->font.loadFromFile("../data/fonts/orange kid.ttf");
    this->text = sf::Text("", font, 30);
    this->input_chart = std::make_shared<Input_Chart>(this->window);
	this->horiz_scrollbar = std::make_shared<Horizontal_Scrollbar>(sf::Vector2f(16.0f, this->WINDOW_SIZE.y - 120.0f), sf::Vector2f(this->WINDOW_SIZE.x - 32.0f, WINDOW_SIZE.y * 0.02f), this->window);
	this->play_button = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x / 2.0f, this->WINDOW_SIZE.y - 64.0f), sf::Vector2f(32.0f, 32.0f), this->text, sf::Color::White);
	this->stop_button = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x / 2.0f - 64.0f, this->WINDOW_SIZE.y - 64.0f), sf::Vector2f(32.0f, 32.0f), this->text, sf::Color::White);
	this->chart_button = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x / 2.0f + 64.0f, this->WINDOW_SIZE.y - 64.0f), sf::Vector2f(32.0f, 32.0f), this->text, sf::Color::White);

    this->text.setPosition(sf::Vector2f(this->WINDOW_SIZE.x/1.5f, this->WINDOW_SIZE.y - 64.0f - this->text.getCharacterSize()/2.0f));

	this->graphics_list.push_back(this->horiz_scrollbar);
    this->graphics_list.push_back(this->input_chart);
	this->button_list.push_back(this->play_button);
	this->button_list.push_back(this->stop_button);
	this->button_list.push_back(this->chart_button);

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
					WINDOW_SIZE.x = event.size.width;
					WINDOW_SIZE.y = event.size.height;
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

                        case sf::Event::TextEntered:
                            // if(this->textfield->getOutlineColor() == sf::Color::Blue)
                            break;
                    }

                    case sf::Event::MouseButtonPressed:
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))   
                        {                     
                            for(auto button : this->button_list)
                                {
                                    if(button->clicked(this->window))
                                    {
                                        if((button == this->play_button)) 
                                        {
                                            if(this->music_player->isPlaying())
                                                this->music_player->pause();
                                            else
                                                this->music_player->play();
                                        }
                                        else if(button == this->stop_button)
                                            this->music_player->stop();
                                        
                                        else if(button == this->chart_button)
                                        {
                                            this->chart_music();
                                        }	
                                    }
                                }
                            this->input_chart->isClicked(this->window);
                            // for(auto input : this->input_chart->getInputList())
                            // {
                            //     if(this->input_chart->isClicked(this->window))
                            //         input->setFillColor(sf::Color::White);
                            //     else
                            //         input->setFillColor(sf::Color::Green);
                            // }
                        }
                        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            //TODO: click the correct square

                            //search through binary search tree
                            for(auto input : this->input_chart->getInputList())
                            {
                                this->input_chart->isClicked(this->window);
                            }
                        }
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
        if(int(i)%6 == 0)
        {
            counter = 0;
            this->input_chart->addInput(16 + i*16, this->WINDOW_SIZE.y, i*16);
        }
    }
}


void Chart_View::chart_music()
{
    this->input_chart->addInput(this->horiz_scrollbar->getSliderPos().x, this->WINDOW_SIZE.y, this->music_player->getPlayTime());
}


void Chart_View::draw()
{   
    this->window->clear();
    
    for(auto button : button_list)
        button->draw(this->window);
    for(auto element : graphics_list)
        element->draw(this->window);
    
    this->window->draw(text);
    this->window->display();
}


void Chart_View::update(const float& dt)
{   
    this->horiz_scrollbar->autoScroll(this->window, this->music_player); 
    this->text.setString(this->music_player->getText());
    this->music_player->updateText();
    
    pollInput();
    draw();
}