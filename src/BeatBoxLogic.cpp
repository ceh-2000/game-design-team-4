#include "BeatBoxLogic.h"

/*
Constructor for the beat box class

Handles animations that need to move before the beat
and be at a specified position on the beat
*/
BeatBoxLogic::BeatBoxLogic(sf::Vector2f startPos, sf::Vector2f endPos, sf::Vector2f postHitPos, sf::Vector2f velocity,
                           float songTimeHit) {
    this->startPos = startPos;
    this->endPos = endPos;
    this->postHitPos = postHitPos;
    this->velocity = velocity;
    this->songTimeHit = songTimeHit;
    this->curPos = startPos;
    normalizeVelocity();
}

/*
We want the box to move in a straight line to it's destination, 
so let's fix the velocity vector to ensure straight line movement
*/
void BeatBoxLogic::normalizeVelocity() {
    float theta = atan(std::abs(this->curPos.y - this->endPos.y) / std::abs(this->curPos.x - this->endPos.x));
    float totalVelocity = sqrt(pow(this->velocity.x, 2) + pow(this->velocity.y, 2));
    velocity.x = totalVelocity * cos(theta);
    velocity.y = totalVelocity * sin(theta);

    std::cout << velocity.x << std::endl;
    std::cout << velocity.x << std::endl;

}

/*
Move our BeatBox the correct x-amount toward the target end position
*/
void BeatBoxLogic::moveX(const float &deltaTime) {
    // Move to the left to reach the end position
    if (this->curPos.x > this->endPos.x) {
        this->curPos.x = this->curPos.x - std::abs(velocity.x) * deltaTime;
    }
        // Move to the right to reach the end position
    else {
        this->curPos.x = this->curPos.x + std::abs(velocity.x) * deltaTime;
    }
}

/*
Move our BeatBox the correct y-amount toward the target final position
*/
void BeatBoxLogic::moveY(const float &deltaTime) {
    // Move to the left to reach the end position
    if (this->curPos.y > this->endPos.y) {
        this->curPos.y = this->curPos.y - std::abs(velocity.y) * deltaTime;
    }
        // Move to the right to reach the end position
    else {
        this->curPos.y = this->curPos.y + std::abs(velocity.y) * deltaTime;
    }
}

/*
Move our BeatBox the correct x-amount toward the target post-hit position

Allows us to keep moving the block even after the "hit"
*/
void BeatBoxLogic::moveXAfter(const float &deltaTime) {
    // Move to the left to reach the end position
    if (this->curPos.x > this->postHitPos.x) {
        this->curPos.x = this->curPos.x - std::abs(velocity.x) * deltaTime;
    }
        // Move to the right to reach the end position
    else {
        this->curPos.x = this->curPos.x + std::abs(velocity.x) * deltaTime;
    }
}

/*
Move our BeatBox the correct y-amount toward the target post-hit position

Allows us to keep moving the block even after the "hit"
*/
void BeatBoxLogic::moveYAfter(const float &deltaTime) {
    // Move to the left to reach the post hit position
    if (this->curPos.y > this->postHitPos.y) {
        this->curPos.y = this->curPos.y - std::abs(velocity.y) * deltaTime;
    }
        // Move to the right to reach the post hit position
    else {
        this->curPos.y = this->curPos.y + std::abs(velocity.y) * deltaTime;
    }
}

/*
Update the position of our box that will indicate the beat.

Return true if we can make it to our end position before the hit and false otherwise.
*/
bool BeatBoxLogic::update(const float &deltaTime, const float &curSongTime) {
    // How long until box needs to be at its end position
    float timeUntilHit = songTimeHit - curSongTime;

    // Move the beat box to the end position; time has run out.
    if (timeUntilHit <= 0 && !postHitMove) {
        this->curPos = this->endPos;
        this->postHitMove = true;
    } else if (postHitMove && this->curPos.x - this->postHitPos.x < 0.1 && this->curPos.y - this->postHitPos.y < 0.1) {
        moveXAfter(deltaTime);
        moveYAfter(deltaTime);
    }
    else if(postHitMove){
        this->curPos = this->postHitPos;
    }
    else {
        // Determine if it's time to move
        float timeToTravelX = std::abs(this->endPos.x - this->curPos.x) / std::abs(this->velocity.x);
        float timeToTravelY = std::abs(this->endPos.y - this->curPos.y) / std::abs(this->velocity.y);
        float timeToTravel = std::max(timeToTravelX, timeToTravelY);

        // float speed = sqrt(pow(this->velocity.x, 2)+pow(this->velocity.y, 2));
        // float distance = sqrt(pow(this->endPos.x - this->curPos.x, 2) + pow(this->endPos.y - this->curPos.y, 2));
        // float timeToTravel = distance / speed;

        if (timeUntilHit <= timeToTravel) {
            moveX(deltaTime);
            moveY(deltaTime);
        }

        // if(timeUntilHit <= timeToTravelY){
        //     moveY(deltaTime);
        // }

        if (timeToTravel - timeUntilHit > 0.1) {
            std::cout << "Time to travel: " << timeToTravel << " Time to hit: " << timeUntilHit << std::endl;
            return false;
        }
    }
    return true;

}