#include "input_chart.h"

Input_Chart::Input_Chart(std::shared_ptr<sf::RenderWindow> window) : GUI_Element()
{
	this->window = window;
}


//detect if inside
bool Input_Chart::isClicked(std::shared_ptr<sf::RenderWindow> window)
{
	this->pixelPos = sf::Mouse::getPosition(*window);
	this->worldPos = window->mapPixelToCoords(this->pixelPos);
	for(auto input : this->inputList)
	{
		if (this->worldPos.x >= input->getPosition().x
		&& this->worldPos.x <= input->getPosition().x + input->getSize().x
		&& this->worldPos.y >= input->getPosition().y
		&& this->worldPos.y <= input->getPosition().y + input->getSize().y)
			{
				input->setFillColor(sf::Color::White);
				return true;
			}
		input->setFillColor(sf::Color::Green);
		return false;
	}

	for(auto line : this->lines)
	{
		if (this->worldPos.x >= line->getPosition().x
		&& this->worldPos.x <= line->getPosition().x + line->getSize().x
		&& this->worldPos.y >= line->getPosition().y
		&& this->worldPos.y <= line->getPosition().y + line->getSize().y)
			{
				line->setFillColor(sf::Color(211,211,211,32));
				return true;
			}
		line->setFillColor(sf::Color::White);
		return false;
	}
	return 0;
}

/*
Create a new std::shared_ptr<sf::RectangleShape> and add it to the inputList
Take in timing
*/
void Input_Chart::addInput(float x, float y, float time)
{
	this->timings.push_back(time);
	std::shared_ptr<sf::RectangleShape> input = std::make_shared<sf::RectangleShape>();
	input->setPosition(x, y/2.0f);
	input->setSize(sf::Vector2f(16.0f,32.0f));
	input->setOrigin(sf::Vector2f(8.0f, 16.0f));
	input->setOutlineThickness(5);
	input->setOutlineColor(sf::Color(187,188,188,255));
	input->setFillColor(sf::Color::Green);

	std::shared_ptr<sf::RectangleShape> line = std::make_shared<sf::RectangleShape>();
	line->setPosition(x, y/2.0f);
	line->setSize(sf::Vector2f(1.0f,this->window->getSize().y/2.0f));
	line->setOrigin(sf::Vector2f(0.5f, this->window->getSize().y/4.0f));
	line->setFillColor(sf::Color::White);

	this->inputList.push_back(input);
	this->lines.push_back(line);
}

void Input_Chart::delInput(std::shared_ptr<sf::RectangleShape> input) //binary search
{	
	int i = 0;
	for(auto itr = this->inputList.begin(); itr < this->inputList.end(); ++itr)
	{
		if(this->inputList.at(i) == input)
		{
			this->inputList.erase(itr);
			this->timings.erase(this->timings.begin()+(--i));
		}
		break;
		++i;
	}
}

void Input_Chart::draw(std::shared_ptr<sf::RenderWindow> window)
{   
	for(auto input : this->inputList)
		window->draw(*input);
	for(auto line: this->lines)
		window->draw(*line);
}

void Input_Chart::exportInput()
{
	this->jsonChart->saveJSON("", this->timings);
}