#ifndef HORIZONTAL_SCROLLBAR_H
#define HORIZONTAL_SCROLLBAR_H

#include "gui_element.h"
#include "music_player.h"

class Horizontal_Scrollbar : public GUI_Element
{
private:
    sf::RectangleShape bar;
    sf::RectangleShape slider;

    sf::Vector2i pixelPos;
    sf::Vector2f worldPos;

    sf::Vector2f startPos;
    sf::Vector2f currentPos;
    
public:
    Horizontal_Scrollbar(sf::Vector2f pos, sf::Vector2f dim, std::shared_ptr<sf::RenderWindow> window);
    sf::Vector2f getSliderPos() {return slider.getPosition();}
    void scroll(std::shared_ptr<sf::RenderWindow> window);
    void autoScroll(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Music_Player> music_player);
    void draw(std::shared_ptr<sf::RenderWindow> window);
};

#endif