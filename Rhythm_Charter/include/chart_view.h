#ifndef CHART_VIEW_H
#define CHART_VIEW_H

#include "chart_logic.h"

/*//////////
// the main View of the program
*///////////

class Chart_View
{
	private:
		std::shared_ptr<sf::RenderWindow> window;		
		std::shared_ptr<Chart_Logic> chart_logic;
		std::shared_ptr<Music_Player> music_player;
		std::vector<std::shared_ptr<GUI_Element>> GUIList;
		std::shared_ptr<Horizontal_Scrollbar> horiz_scrollbar;
		std::shared_ptr<Input_Chart> input_chart;

		sf::Font font;
		sf::Text text;
		sf::Text volume;
		// sf::Text fileText;
		// std::string filePath;
		std::shared_ptr<sf::Text> play_time;

		sf::Vector2i startPos;
		sf::Vector2f endPos;

		sf::Vector2i pixelPos;
		sf::Vector2f worldPos;		
		sf::Vector2f WINDOW_SIZE;

	public:
		Chart_View(std::shared_ptr<Chart_Logic> chart_logic);

		void demoChart();
		void chart_music();
		void autoScroll();
		void pollInput();
		void draw();
		void update();
};

#endif