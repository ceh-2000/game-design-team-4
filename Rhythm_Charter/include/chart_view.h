#ifndef CHART_VIEW_H
#define CHART_VIEW_H

#include "chart_logic.h"
#include "gui_element.h"
#include "horizontal_scrollbar.h"
#include "button.h"
#include "input_chart.h"
#include "music_player.h"

class Chart_View
{
	private:
		std::shared_ptr<sf::RenderWindow> window;
		
		std::shared_ptr<Music_Player> music_player;
		std::shared_ptr<Chart_Logic> chart_logic;

		sf::Font font;
		sf::Text text;

		std::vector<std::shared_ptr<GUI_Element>> graphics_list;
		std::vector<std::shared_ptr<Button>> button_list;
		
		std::shared_ptr<Button> play_button;
		std::shared_ptr<Button> stop_button;
		std::shared_ptr<Button> chart_button;
		std::shared_ptr<Horizontal_Scrollbar> horiz_scrollbar;
		std::shared_ptr<Input_Chart> input_chart;

		sf::Vector2f WINDOW_SIZE;

	public:
		Chart_View(std::shared_ptr<Chart_Logic> chart_logic);
		void init();

		void demoChart();
		void chart_music();

		void autoScroll();

		void pollInput();
		void draw();
		void update(const float& dt);
};

#endif