#ifndef VIEW_PANEL_H
#define VIEW_PANEL_H
#include <SFML/Graphics.hpp>
#include "gui_element.h"
#include "input_chart.h"

class View_Panel : public GUI_Element
{
private:
  sf::Vector2f WINDOW_SIZE = sf::Vector2f(1280.0f, 800.0f);
  sf::RectangleShape panel;
  sf::RectangleShape slider;
  std::vector<Input_Chart> view_inputs;
public:
  View_Panel(sf::Vector2f panelPos, sf::Vector2f panelDim, sf::Vector2f sliderPos, TYPE type);
  sf::RectangleShape getPanel() { return panel;}
  sf::RectangleShape getSlider() {return slider;}

  bool selected(sf::Vector2f mousePos);
  void autoScroll(std::shared_ptr<Music_Player> music_player);
  void draw(std::shared_ptr<sf::RenderWindow> window);
};

#endif
