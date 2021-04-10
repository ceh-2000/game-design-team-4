#include "Animation.h"
#include <iostream>
Animation::Animation(bool& animate, float& elapsedDuration, int frames, float timePerFrame, bool loop, sf::Text &text, sf::Sprite &sprite, sf::IntRect &rectText)
{   
    this->sprite = sprite;
    this->text = text;
    this->loop = loop;
    this->texture = rectText;
    this->elapsedDuration = elapsedDuration;
    this->frames = frames;
    this->timePerFrame = timePerFrame;
}

void Animation::animateSprite(const float& dt, std::shared_ptr<sf::RenderWindow> window){

    elapsedDuration += dt;
    std::cout << elapsedDuration << "\n";
    std::cout << timePerFrame << "\n";
    std::cout << "\n";
        while(elapsedDuration > timePerFrame){
            elapsedDuration -= timePerFrame;

            // cycle through 3 frames of talking
            if(!this->loop && counter == frames){
                animate = false;
                this->text.setString("");
                break;
            }
            else if (counter == frames){
                counter = 0;
                texture.left = 0;
            }
            else 
            {
                texture.left += 128;
                counter++;
            }
        }
        //window->clear(sf::Color::Blue);
        this->sprite.setTextureRect(texture);
        window->draw(sprite);
        window->draw(text);
        //window->display();
}    