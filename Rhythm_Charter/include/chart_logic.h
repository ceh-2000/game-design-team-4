#ifndef CHART_LOGIC_H
#define CHART_LOGIC_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "gui_element.h"
#include "horizontal_scrollbar.h"
#include "input_chart.h"
#include "music_player.h"
#include "button.h"

/*///////////////////////////////
// main LOGIC for rhythm charter
*////////////////////////////////
class Chart_Logic
{
private:
	bool activeState = true;
	sf::Vector2f WINDOW_SIZE = sf::Vector2f(1280.0f, 800.0f);
	std::vector<std::shared_ptr<GUI_Element>> GUIList;
	std::vector<std::shared_ptr<Button>> buttonList;

	std::shared_ptr<Music_Player> music_player;
	std::shared_ptr<Button> textField;
	std::shared_ptr<Button> play_button;
	std::shared_ptr<Button> stop_button;
	std::shared_ptr<Button> chart_button;
	std::shared_ptr<Horizontal_Scrollbar> horiz_scrollbar;
	std::shared_ptr<Input_Chart> input_chart;

public:
	Chart_Logic();
	void init();
	void setActive(bool a) { activeState = a; }
	bool getActive() { return activeState; }
	void setWindowSize(sf::Vector2f w) { WINDOW_SIZE = w; }
	sf::Vector2f getWindowSize() { return WINDOW_SIZE; }
	std::vector<std::shared_ptr<GUI_Element>> &getGUIList() { return GUIList;}
	std::vector<std::shared_ptr<Button>> &getButtonList() { return buttonList; }
	std::shared_ptr<Music_Player> &getMusic() { return music_player; }
    std::shared_ptr<Input_Chart> &getChart() { return input_chart; }
    std::shared_ptr<Horizontal_Scrollbar> &getScrollBar() { return horiz_scrollbar; }
};
#endif