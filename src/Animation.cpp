#include "Animation.h"

/*
 * Constructor for Animation class that wraps sprite class to provide generalized animations for a sprite sheet
 */
Animation::Animation(const std::string &spriteName, const sf::Vector2f &dimensions, const bool &loop) {

    // Establish variables to loop or not loop animation and determine box dimensions
    this->loop = loop;
    this->dimensions = dimensions;

    // Load in sprite sheet file
    if (!this->spriteSheet.loadFromFile("../data/art/sprite_sheet.png")) {
        std::cout << "Could not load sprite sheet from file." << std::endl;
    }

    // Determine which row corresponds to our animation of interest
    int count = 0;
    for (const char *spriteType: this->spriteNames) {
        if (std::strcmp(spriteType, spriteName.c_str()) == 0) {
            this->rowNumber = count;
            break;
        } else {
            count++;
        }
    }

    // Create sprite basics
    this->sprite.setTexture(this->spriteSheet);
    this->boundingBox = sf::IntRect(0, this->boxSize*this->rowNumber, this->boxSize, this->boxSize);
    this->sprite.setTextureRect(this->boundingBox);
    this->sprite.scale(dimensions.x/boxSize, dimensions.y/this->boxSize);
}


/*
 * Transition sprite texture to a new frame
 */
void Animation::update(const float &deltaTime){
    this->elapsedTime += deltaTime;

    if(this->elapsedTime < this->maxTimeToShowFrame){
        if(!this->loop && this->counter == this->frameNumber[this->rowNumber]){
            boundingBox.left = 0;
        }
        else if(this->counter == this->frameNumber[this->rowNumber]){
            this->counter = 0;
            this->boundingBox.left = 0;
        }
        else{
            this->boundingBox.left += this->boxSize;
            this->counter++;
        }
    }
    this->sprite.setTextureRect(boundingBox);
}

