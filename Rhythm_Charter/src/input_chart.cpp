#include "input_chart.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Input_Chart::Input_Chart(std::shared_ptr<Horizontal_Scrollbar> horiz_scrollbar, std::shared_ptr<Music_Player> mp, TYPE type) : GUI_Element(type)
{
	this->horiz_scrollbar = horiz_scrollbar;
	this->mp = mp;
	this->selection = std::make_shared<sf::RectangleShape>();
	this->selection->setFillColor(sf::Color::Transparent);
	this->selection->setOutlineColor(sf::Color::Magenta);
	this->selection->setOutlineThickness(5.0f);
}

//Check if a certain beat is selected
bool Input_Chart::selected(sf::Vector2f mousePos)
{
	int counter = 0;
	//A sorted vector is better to use than a binary search tree as there are no cache misses in comparison
	if(!this->sorted)
	{
		std::sort(this->inputList.begin(), this->inputList.end());
		this->sorted = true;
	}
	//detect if cursor inside
	for(auto itr = this->inputList.begin(); itr < this->inputList.end(); ++itr)
		if(mousePos.x >= (*itr)->getPosition().x
		&& mousePos.x <= (*itr)->getPosition().x + (*itr)->getSize().x
		&& mousePos.y >= (*itr)->getPosition().y
		&& mousePos.y <= (*itr)->getPosition().y + (*itr)->getSize().y)
			{
				(*itr)->setFillColor(sf::Color::White);
				// this->timingText.at(counter)->setFillColor(sf::Color::White);
				counter++;
				return true;
			}
	return false;
}

/*//////////////////////////////////////////////////////////////////////////
Create a new std::shared_ptr<sf::RectangleShape> and add it to the inputList
Take in timing
*///////////////////////////////////////////////////////////////////////////
void Input_Chart::addInput(float x, float y, float time, sf::Font &font)
{
	std::cout << "P: " << x << std::endl;
	std::cout<< "t: " << time << std::endl;
	this->timings.push_back(time);
	std::shared_ptr<sf::RectangleShape> input = std::make_shared<sf::RectangleShape>();
	input->setPosition(x, y/2.0f);
	input->setSize(sf::Vector2f(8.0f,32.0f));
	input->setOrigin(sf::Vector2f(4.0f, 16.0f));
	input->setOutlineThickness(5);
	input->setOutlineColor(sf::Color(187,188,188,255));
	input->setFillColor(sf::Color::Green);
	this->inputList.push_back(input);

	if(x<this->minX)
	{
		this->selection->setPosition(x, this->selection->getSize().y);
		this->selection->setSize(sf::Vector2f((x - this->minX), this->selection->getSize().y));
		this->minX = x;
	}
	if(x+8.0f>this->maxX)
	{
		this->maxX = x+8.0f;
		this->selection->setSize(sf::Vector2f(this->maxX, this->selection->getSize().y));
	}
	if(y<this->minY)
	{
		this->selection->setPosition(this->selection->getSize().x, y-this->selection->getSize().y/2.0f);
		this->selection->setSize(sf::Vector2f(this->selection->getSize().x, (y-this->maxY)));
		this->minY = y - this->selection->getSize().y/2.0f;
	}

	if(y+32.0f>this->maxY)
	{
		this->maxY = y+32.0f;
		this->selection->setSize(sf::Vector2f(this->selection->getSize().x, this->maxY));
	}

	std::shared_ptr<sf::Text> beatLabel = std::make_shared<sf::Text>(std::to_string(time), font, 20);
	beatLabel->setPosition(sf::Vector2f(x, y/2.0f+32.0f));
	beatLabel->setOrigin(sf::Vector2f(5.0f, 5.0f));
	beatLabel->setFillColor(sf::Color::Transparent);
	this->timingText.push_back(beatLabel);
	this->sorted = false;
}


void Input_Chart::delInput()
{
	this->counter = 0;
	for(auto itr = this->inputList.begin(); itr < this->inputList.end(); ++itr)
	{
		if((*itr)->getFillColor() == sf::Color::White)
		{
			this->inputList.erase(itr);
			this->timings.erase(this->timings.begin()+this->counter);
			this->timingText.erase(this->timingText.begin()+this->counter);
		}
		++this->counter;
	}
}

void Input_Chart::clearInput()
{
	this->counter = 0;
	for(auto itr = this->inputList.begin(); itr < this->inputList.end(); ++itr)
	{
		this->inputList.erase(itr);
		this->timings.erase(this->timings.begin()+this->counter);
		this->timingText.erase(this->timingText.begin()+this->counter);
		++this->counter;
	}
}


void Input_Chart::moveInput(sf::Vector2f mousePos, float size)
{
	this->counter = 0;
	for(auto itr = this->inputList.begin(); itr < this->inputList.end(); ++itr)
	{
		if((*itr)->getFillColor() == sf::Color::White)
		{
			//select
			(*itr)->setPosition(mousePos);
			this->timings.at(counter) = this->mp->getDuration()*((mousePos.x-this->horiz_scrollbar->getSlider().getSize().y)/(this->horiz_scrollbar->getBar().getSize().x));

			std::cout<<"New Time: " << this->timings.at(counter) <<std::endl;
			(*itr)->setFillColor(sf::Color::Green);
		}
		this->counter++;
	}
}

void Input_Chart::selectAll()
{
	// for(auto itr = this->inputList.begin(); itr<this->inputList.end(); ++itr)
	// 	{
	// 		(*itr)->setFillColor(sf::Color::White);
	// 		(*itr)->getSize()
	// 	}
}

void Input_Chart::draw(std::shared_ptr<sf::RenderWindow> window)
{
	for(auto input : this->inputList)
		window->draw(*input);
	for(auto string: this->timingText)
		window->draw(*string);
	window->draw(*selection);
}

void Input_Chart::saveJSON()
{
	if(std::distance(this->timings.begin(), this->timings.end()) != 0)
		std::sort(this->timings.begin(), this->timings.end());
	nlohmann::json jsonfile;
	for(auto itr = this->timings.begin(); itr<this->timings.end(); ++itr) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << *itr;
		std::string s = stream.str();
		jsonfile["death_by_glamour0"] += s;
	}

	std::ofstream file("../timingChart.json");
	file << jsonfile;
}

std::vector<float> Input_Chart::loadJSON()
{
	std::vector<float> timings;
	std::ifstream fileStream("../timingChart.json");
	nlohmann::json jTimings = nlohmann::json::parse(fileStream);

	timings.push_back(jTimings["test"]);
	return timings;
}
