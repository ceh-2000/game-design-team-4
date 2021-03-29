#ifndef INPUT_CHART_H
#define INPUT_CHART_H

#include <fstream>
#include <ostream>
#include "../../include/json.h"
#include "gui_element.h"
#include "music_player.h"
#include "horizontal_scrollbar.h"

class Input_Chart : public GUI_Element
{
private:
	std::shared_ptr<Horizontal_Scrollbar> horiz_scrollbar;
	std::shared_ptr<Music_Player> mp;
	std::vector<std::shared_ptr<sf::RectangleShape>> inputList;
	std::vector<float> timings; //in seconds
	std::vector<std::shared_ptr<sf::Text>> timingText;
	bool sorted = false;
	int counter;

public:
	Input_Chart(std::shared_ptr<Horizontal_Scrollbar> horiz_scrollbar, std::shared_ptr<Music_Player> mp, TYPE type);

	std::vector<std::shared_ptr<sf::RectangleShape>> getInputList() { return inputList; }
	std::vector<float> getTimings() { return timings; }
	
	bool selected(sf::Vector2f mousePos);
	void selectAll();
	
	void addInput(float x, float y, float time, sf::Font &font);
	void delInput();
	void moveInput(sf::Vector2f mousePos, float size);
	void clearInput();

	void draw(std::shared_ptr<sf::RenderWindow> window);

	void saveJSON();
    std::vector<float> loadJSON();
};

#endif