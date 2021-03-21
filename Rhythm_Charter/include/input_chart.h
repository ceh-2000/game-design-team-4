#ifndef INPUT_CHART_H
#define INPUT_CHART_H

#include "importChart.h"
#include "exportChart.h"
#include "gui_element.h"

class Input_Chart : public GUI_Element
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::vector<std::shared_ptr<sf::RectangleShape>> inputList;
	std::vector<std::shared_ptr<sf::RectangleShape>> lines;
	std::vector<float> timings;

	sf::Vector2i pixelPos;
	sf::Vector2f worldPos;

public:
	Input_Chart(std::shared_ptr<sf::RenderWindow> window);

	std::vector<std::shared_ptr<sf::RectangleShape>> getInputList() { return inputList; }

	bool isClicked(std::shared_ptr<sf::RenderWindow> window);

	void addInput(float x, float y, float time);
	void delInput(std::shared_ptr<sf::RectangleShape> input);
	void moveInput(std::shared_ptr<sf::RenderWindow> window);

	void importInput();
	void exportInput();

	void draw(std::shared_ptr<sf::RenderWindow> window);
};

#endif