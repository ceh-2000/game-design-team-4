#include "Animation.h"
#include <iostream>
Animation::Animation(float& elapsedDuration, int frames, float timePerFrame, sf::Sprite &sprite, sf::IntRect &rectText)
{   
    //this->sprite = sprite;
    this->texture = rectText;
    this->elapsedDuration = elapsedDuration;
    this->frames = frames;
    this->timePerFrame = timePerFrame;
}

void Animation::animateSprite(const float& dt, std::shared_ptr<sf::RenderWindow> window, sf::Text &text){

    elapsedDuration += dt;

        //std::cout << elapsedDuration << "\n";
        while(elapsedDuration > timePerFrame){
            elapsedDuration -= timePerFrame;
            std::cout << "IN";
            if (counter == frames){
                this->text.setString("");
                counter = 0;
                texture.left = 0;
                break;
            }
            else 
            {
                texture.left += 128;
                counter++;
            }
        }

        this->sprite.setTextureRect(texture);
}    



void Animation::animateSprite(const float& dt, std::shared_ptr<sf::RenderWindow> window){

    elapsedDuration += dt;
        while(elapsedDuration > timePerFrame){
            elapsedDuration -= timePerFrame;

            // cycle through 3 frames of talking
            if(!this->loop && counter == frames){
                std::cout << "END";
                counter = 0;
                texture.left = 0;
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

        this->sprite.setTextureRect(texture);
}    