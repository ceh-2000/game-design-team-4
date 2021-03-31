#include "BeatBoxLogic.h"

BeatBoxLogic::BeatBoxLogic(sf::Vector2f startPos, sf::Vector2f endPos, sf::Vector2f velocity, float songTimeHit)
{
    this->startPos = startPos;
    this->endPos = endPos;
    this->velocity = velocity;
    this->songTimeHit = songTimeHit;
    this->curPos = sf::Vector2f(500.0f, 500.0f);
}

void BeatBoxLogic::setVelocity(sf::Vector2f vel)
{
    // At some point, set velocity so we ensure our animation will always happen as expected
}

void BeatBoxLogic::move(float deltaTime)
{   
    // TODO: AVOID OVERSHOOTING WITH VELOCITY!
    this->curPos = this->curPos + velocity * deltaTime;
}

/*
Update the position of our box that will indicate the beat.

Return true if we're not at our end position yet and false otherwise.
*/
void BeatBoxLogic::update(float deltaTime, float curSongTime)
{
    // How long until box needs to be at its end position
    float timeUntilHit = songTimeHit - curSongTime;

    // Move the beat box to the end position; time has run out.
    if(timeUntilHit <= 0){
        this->curPos = this->endPos;
    }
    else{
        // Determine if it's time to move
        float speed = sqrt(pow(this->velocity.x, 2)+pow(this->velocity.y, 2));
        float distance = sqrt(pow(this->endPos.x - this->startPos.x, 2) + pow(this->endPos.y - this->startPos.y, 2));
        float timeToTravel = distance / speed;
        std::cout << timeToTravel << std::endl;

        if(timeUntilHit <= timeToTravel){
            move(deltaTime);
        }
    }

}