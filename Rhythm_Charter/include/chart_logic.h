#ifndef CHART_LOGIC_H
#define CHART_LOGIC_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "inputBST.h"
#include "guiElementBST.h"

class Chart_Logic
{
private:
	bool activeState = true;
	sf::Vector2f WINDOW_SIZE = sf::Vector2f(1280.0f, 800.0f);
	std::shared_ptr<InputBST> inputBST;
	
public:
	Chart_Logic();
	void setActive(bool a) { activeState = a; }
	bool getActive() { return activeState; }
	
	void setWindowSize(sf::Vector2f w) { WINDOW_SIZE = w; } 
	sf::Vector2f getWindowSize() { return WINDOW_SIZE; }
};

#endif