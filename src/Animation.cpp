#include "Animation.h"
<<<<<<< Updated upstream
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
=======

Animation::Animation(sf::Sprite& sprite, int row, int frames, int sizePerFrame, float timePerFrame, bool loop)
{   
   this->row = row;
   this->frames = frames;
   this->sizePerFrame = sizePerFrame;
   this->timePerFrame = timePerFrame;
   this->elapsedDuration = this->timePerFrame;
   this->sprite = sprite;
   
   this->counter = 0;
   textureRect = sf::IntRect(0, 100, sizePerFrame, sizePerFrame);
   this->sprite.setTextureRect(textureRect);

}

void Animation::animate(const float& dt, std::shared_ptr<sf::RenderWindow> window){
>>>>>>> Stashed changes

    this->elapsedDuration += dt;

<<<<<<< Updated upstream
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
=======
    while(elapsedDuration > timePerFrame){
        elapsedDuration -= timePerFrame;

        if(!this->loop && counter == frames){
            textureRect.left = 0;
            break;
        }
        else if (counter == frames){
            counter = 0;
            textureRect.left = 0;
        }
        else 
        {
            textureRect.left += sizePerFrame;
            counter++;
        }
    }
    
    this->sprite.setTextureRect(textureRect);
>>>>>>> Stashed changes
}    