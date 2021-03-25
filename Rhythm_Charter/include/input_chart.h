#ifndef INPUT_CHART_H
#define INPUT_CHART_H

#include <fstream>
#include <ostream>
#include "gui_element.h"
#include "../../include/json.h"

class Input_Chart : public GUI_Element
{
private:
	std::vector<std::shared_ptr<sf::RectangleShape>> inputList;
	std::vector<std::shared_ptr<sf::RectangleShape>> lines;

	bool sorted = false;

	std::vector<float> timings; //in seconds

public:
	Input_Chart();

	std::vector<std::shared_ptr<sf::RectangleShape>> getInputList() { return inputList; }

	bool selected(sf::Vector2f mousePos);

	void addInput(float x, float y, float time);
	void delInput(std::shared_ptr<sf::RectangleShape> input);
	void moveInput(std::shared_ptr<sf::RenderWindow> window);

	void saveJSON();
    std::vector<float> loadJSON();

	std::vector<float> getTimings() { return timings; }

	void draw(std::shared_ptr<sf::RenderWindow> window);
};

#endif