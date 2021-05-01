#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Sprite& sprite, int startY, int frames, int frameX, int frameY, float timePerFrame, bool loop) : sprite(sprite)
{   
   this->sprite = sprite;
   this->startY = startY; //Y position of first frame in the row
   this->frames = frames;
   this->frameX = frameX; //width of each frame
   this->frameY = frameY; //height of each frame
   this->timePerFrame = timePerFrame;
   this->loop = loop;

   this->elapsedDuration = this->timePerFrame;
   this->counter = 0;

   textureRect = sf::IntRect(0, this->startY, this->frameX, this->frameY);
   this->sprite.setTextureRect(textureRect);

}

void Animation::animate(const float& dt, std::shared_ptr<sf::RenderWindow> window){
    this->elapsedDuration += dt;

    while(elapsedDuration > timePerFrame){
        elapsedDuration -= timePerFrame;


        if(!this->loop && counter == frames-1){
            textureRect.left = 0;
            break;
        }
        else if (counter == frames-1){
            counter = 0;
            textureRect.left = 0;
        }
        else 
        {
            textureRect.left += frameX;
            counter++;
        }
    }
    
    this->sprite.setTextureRect(textureRect);

    if(!this->loop && counter == frames-1){
        std::cout << "Don't draw";
    }
    else{
        window->draw(sprite);
    }

}