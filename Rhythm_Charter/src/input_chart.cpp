#include "input_chart.h"

Input_Chart::Input_Chart() : GUI_Element(){}

//detect if inside
bool Input_Chart::selected(sf::Vector2f mousePos)
{
	if(!this->sorted)
	{
		std::sort(this->inputList.begin(), this->inputList.end());
		this->sorted = true;
	}
	for(auto itr = this->inputList.begin(); itr < this->inputList.end(); ++itr)
		if(mousePos.x >= (*itr)->getPosition().x
	&& mousePos.x <= (*itr)->getPosition().x + (*itr)->getSize().x
	&& mousePos.y >= (*itr)->getPosition().y
	&& mousePos.y <= (*itr)->getPosition().y + (*itr)->getSize().y)
			(*itr)->setFillColor(sf::Color::White);

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
	this->inputList.push_back(input);

	std::shared_ptr<sf::RectangleShape> line = std::make_shared<sf::RectangleShape>();
	line->setPosition(x, y/2.0f);
	line->setSize(sf::Vector2f(1.0f, 50.0f));
	line->setOrigin(sf::Vector2f(0.5f, 25.0f));
	line->setFillColor(sf::Color::White);
	this->lines.push_back(line);

	this->sorted = false;
}

void Input_Chart::delInput(std::shared_ptr<sf::RectangleShape> input) 
{	
	int i = 0;
	for(auto itr = this->inputList.begin(); itr < this->inputList.end(); ++itr)
	{
		if(this->inputList.at(i) == input)
		{
			this->inputList.erase(itr);
			this->lines.erase(this->lines.begin()+(--i));
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

void Input_Chart::saveJSON()
{
	nlohmann::json jsonfile;

	for(auto itr = this->timings.begin(); itr<this->timings.end(); ++itr)
		jsonfile["test"] += *itr;

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