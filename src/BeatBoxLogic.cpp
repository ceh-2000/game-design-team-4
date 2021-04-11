#include "BeatBoxLogic.h"

BeatBoxLogic::BeatBoxLogic(sf::Vector2f startPos, sf::Vector2f endPos, sf::Vector2f velocity, float songTimeHit)
{
    this->startPos = startPos;
    this->endPos = endPos;
    this->velocity = velocity;
    this->songTimeHit = songTimeHit;
    this->curPos = startPos;
}

void BeatBoxLogic::setVelocity(sf::Vector2f vel)
{
    // At some point, set velocity so we ensure our animation will always happen as expected
    // or we need a delay at first so user doesn't lose points when first few boxes don't make it in time
}

void BeatBoxLogic::move(float deltaTime)
{   
    moveX(deltaTime);
    moveY(deltaTime);
}

/*
Move our BeatBox the correct x-amount toward the target end position
*/
void BeatBoxLogic::moveX(float deltaTime){
    // Move to the left to reach the end position
    if(this->curPos.x > this->endPos.x){
        this->curPos.x = this->curPos.x - std::abs(velocity.x) * deltaTime;
    }
    // Move to the right to reach the end position
    else{
        this->curPos.x = this->curPos.x + std::abs(velocity.x) * deltaTime;
    }
}

/*
Move our BeatBox the correct x-amount toward the target final position
*/
void BeatBoxLogic::moveY(float deltaTime){
    // Move to the left to reach the end position
    if(this->curPos.y > this->endPos.y){
        this->curPos.y = this->curPos.y - std::abs(velocity.y) * deltaTime;
    }
    // Move to the right to reach the end position
    else{
        this->curPos.y = this->curPos.y + std::abs(velocity.y) * deltaTime;
    }
}

/*
Update the position of our box that will indicate the beat.

Return true if we can make it to our end position before the hit and false otherwise.
*/
bool BeatBoxLogic::update(float deltaTime, float curSongTime)
{
    // How long until box needs to be at its end position
    float timeUntilHit = songTimeHit - curSongTime;

    // Move the beat box to the end position; time has run out.
    if(timeUntilHit <= 0){
        this->curPos = this->endPos;
    }
    else{
        // Determine if it's time to move
        float timeToTravelX = std::abs(this->endPos.x - this->curPos.x) / std::abs(this->velocity.x);
        float timeToTravelY = std::abs(this->endPos.y - this->curPos.y) / std::abs(this->velocity.y);
        float timeToTravel = std::max(timeToTravelX, timeToTravelY);

        // float speed = sqrt(pow(this->velocity.x, 2)+pow(this->velocity.y, 2));
        // float distance = sqrt(pow(this->endPos.x - this->curPos.x, 2) + pow(this->endPos.y - this->curPos.y, 2));
        // float timeToTravel = distance / speed;

        if(timeUntilHit <= timeToTravel){
            move(deltaTime);
        }

        if(timeToTravel - timeUntilHit > 0.1){
            std::cout << "Time to travel: " << timeToTravel << " Time to hit: " << timeUntilHit << std::endl;
            return false;
        }
    }
    return true;

}