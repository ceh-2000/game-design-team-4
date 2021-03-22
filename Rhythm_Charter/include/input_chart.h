#ifndef INPUT_CHART_H
#define INPUT_CHART_H

#include "gui_element.h"
#include "chart_to_json.h"

class Input_Chart : public GUI_Element
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Chart_To_JSON> jsonChart;

	std::vector<std::shared_ptr<sf::RectangleShape>> inputList;
	std::vector<std::shared_ptr<sf::RectangleShape>> lines;

	std::vector<float> timings; //in seconds

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