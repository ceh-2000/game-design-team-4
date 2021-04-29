#ifndef CSCI437_CUTSCENE_H
#define CSCI437_CUTSCENE_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

class CutScene {
private:
    std::shared_ptr<sf::RenderWindow> app;
    sf::Font font;
    sf::Text sceneText;

    int score = 0;
public:
    CutScene(std::shared_ptr<sf::RenderWindow> app);

    void setScore(int s) { this->score = s;}

    void draw(const float &dt);
};

#endif //CSCI437_CUTSCENE_H
