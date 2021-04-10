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
    this->animate = animate;
}

void Animation::animateSprite(const float& dt, std::shared_ptr<sf::RenderWindow> window){

    elapsedDuration += dt;
        while(elapsedDuration > timePerFrame){
            elapsedDuration -= timePerFrame;

            // cycle through 3 frames of talking
            if(!this->loop && counter == frames){
                std::cout << "END";
                this->animate = false;
                this->text.setString("");
                elapsedDuration = timePerFrame;
                counter = 0;
                texture.left = 0;
                break;
            }
            else if (counter == frames-1){
                counter = 0;
                texture.left = 0;
            }
            else 
            {
                texture.left += 128;
                counter++;
            }
        }
        //if(animate){
        this->sprite.setTextureRect(texture);
        window->draw(sprite);
        window->draw(this->text);
        //}
        window->display();
}    