#ifndef HORIZONTAL_SCROLLBAR_H
#define HORIZONTAL_SCROLLBAR_H

#include "gui_element.h"
#include "music_player.h"

/*////////
/ This class adds a horizontal scrollbar and adds scroll and autoscroll functionality 
*/////////

class Horizontal_Scrollbar : public GUI_Element
{
private:
    sf::RectangleShape bar;
    sf::RectangleShape slider;
    
public:
    Horizontal_Scrollbar(sf::Vector2f pos, sf::Vector2f dim, TYPE type);
    sf::RectangleShape getBar() { return bar;}
    sf::RectangleShape getSlider() {return slider;}
    
    bool selected(sf::Vector2f mousePos);
    void autoScroll(std::shared_ptr<Music_Player> music_player);
    void draw(std::shared_ptr<sf::RenderWindow> window);
};

#endif