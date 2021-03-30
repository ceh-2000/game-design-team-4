#include "Animation.h"
Animation::Animation(const float& dt, int frames, float timePerFrame, bool loop, sf::Text &text, sf::Sprite &sprite, sf::IntRect &rectText, sf::RenderWindow& window)
{   
    this->sprite = sprite;
    this->text = text;
    this->loop = loop;
    this->texture = rectText;

    elapsedDuration += dt;
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
        this->sprite.setTextureRect(texture);
}    