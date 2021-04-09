#include "chart_logic.h"

Chart_Logic::Chart_Logic()
{
	// this->music_player = std::make_shared<Music_Player>("../data/music/Gettin' Freaky (Main Menu) - Friday Night Funkin' OST-HQ.ogg");
	//TODO: load list of songs into musicList from JSON
	std::vector<std::string> musicList;
	musicList.push_back("../data/music/Gabby.ogg");
	this->music_player = std::make_shared<Music_Player>(musicList);

    this->play_button = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x / 2.0f, this->WINDOW_SIZE.y - 64.0f), sf::Vector2f(32.0f, 32.0f), TYPE::PLAY_BTN, 0);
	this->stop_button = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x / 2.0f - 64.0f, this->WINDOW_SIZE.y - 64.0f), sf::Vector2f(32.0f, 32.0f), TYPE::STOP_BTN, 1);
	this->chart_button = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x / 2.0f + 64.0f, this->WINDOW_SIZE.y - 64.0f), sf::Vector2f(32.0f, 32.0f), TYPE::CHART_BTN);
	this->textField = std::make_shared<Button>(sf::Vector2f(this->WINDOW_SIZE.x - 64.0f, 16.0f), sf::Vector2f(64.0f, 16.0f), TYPE::TEXTFIELD, -1);
	this->horiz_scrollbar = std::make_shared<Horizontal_Scrollbar>(sf::Vector2f(16.0f, this->WINDOW_SIZE.y - 120.0f), sf::Vector2f(this->WINDOW_SIZE.x - 32.0f, WINDOW_SIZE.y * 0.02f), TYPE::SCROLLBAR);
	this->input_chart = std::make_shared<Input_Chart>(this->horiz_scrollbar, this->music_player,TYPE::INPUT_CHART);

	this->buttonList.push_back(this->play_button);
	this->buttonList.push_back(this->stop_button);
	this->buttonList.push_back(this->chart_button);

	this->GUIList.push_back(this->play_button);
	this->GUIList.push_back(this->stop_button);
	this->GUIList.push_back(this->chart_button);
	this->GUIList.push_back(this->textField);
	this->GUIList.push_back(this->horiz_scrollbar);
	this->GUIList.push_back(this->input_chart);
}