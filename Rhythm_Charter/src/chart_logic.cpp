#include "chart_logic.h"

Chart_Logic::Chart_Logic()
{
    this->play_button = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x / 2.0f, this->WINDOW_SIZE.y - 64.0f), sf::Vector2f(32.0f, 32.0f), sf::Color::White);
	this->stop_button = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x / 2.0f - 64.0f, this->WINDOW_SIZE.y - 64.0f), sf::Vector2f(32.0f, 32.0f), sf::Color::White);
	this->chart_button = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x / 2.0f + 64.0f, this->WINDOW_SIZE.y - 64.0f), sf::Vector2f(32.0f, 32.0f), sf::Color::White);
	this->horiz_scrollbar = std::make_shared<Horizontal_Scrollbar>(sf::Vector2f(16.0f, this->WINDOW_SIZE.y - 120.0f), sf::Vector2f(this->WINDOW_SIZE.x - 32.0f, WINDOW_SIZE.y * 0.02f));
	this->input_chart = std::make_shared<Input_Chart>();

	this->GUIList.push_back(this->play_button);
	this->GUIList.push_back(this->stop_button);
	this->GUIList.push_back(this->chart_button);
	this->GUIList.push_back(this->horiz_scrollbar);
	this->GUIList.push_back(this->input_chart);
}