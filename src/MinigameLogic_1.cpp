#include "MinigameLogic_1.h"

MinigameLogic_1::MinigameLogic_1(std::shared_ptr<Song> song, float x, float y) {
    this->song = song;
    this->windowSize = sf::Vector2f(x, y);
    this->distanceToBowl = y*0.75;
    this->bowlPosition = sf::Vector2f(x / 2.0f - bowlSize.x, distanceToBowl-bowlSize.y);
    this->bowlStartPosition = this->bowlPosition;

    // Create default beat boxes for the entire song of timings from the start
    std::vector<float> allSongTimings = song->getAllTimings();
    for (float time : allSongTimings) {
        float LO = 0.0f;
        float HI = 1.0f;
        float randomNum1 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
        float randomNum2 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

        float startX = windowSize.x/2 + 100;
        if(randomNum1 < 0.5){
            startX = windowSize.x/2 - 100;
        }

        if(randomNum2 < 0.5){
            isGoodVector.push_back(false);
        }
        else{
            isGoodVector.push_back(true);
        }

        beatBoxes.push_back(
                BeatBoxLogic(sf::Vector2f(startX, -ingredientDim.y),
                             sf::Vector2f(startX, distanceToBowl),
                             sf::Vector2f(ingredientSpeed, ingredientSpeed),
                             time));
    }
}

/*
Update all BeatBox positions for pre-hit animations
*/
void MinigameLogic_1::updateBeatBoxes(const float &deltaTime) {
    float curSongTime = song->getSongTime();
    std::vector<BeatBoxLogic> temp;
    int count = 0;
    for (BeatBoxLogic beatBox : beatBoxes) {
        bool canWeMakeIt = beatBox.update(deltaTime, curSongTime);
        if (canWeMakeIt == false) {
            std::cout << "Beat box #: " << count
                      << " can't make it in time :(. Consider increasing the speed of the boxes or adjusting another parameter."
                      << std::endl;
        }
        temp.push_back(beatBox);
        count++;
    }
    this->beatBoxes = temp;
}

void MinigameLogic_1::updateBowl(const float &deltaTime){
    float bowlDisplacement = std::abs(bowlPosition.x - bowlStartPosition.x);
    if(bowlMovingOut && bowlDisplacement < maxAmountToMoveBowl && moveBowl == 1){
        bowlPosition.x += bowlSpeed*deltaTime;
    }
    else if(bowlMovingOut && bowlDisplacement < maxAmountToMoveBowl && moveBowl == 2){
        bowlPosition.x -= bowlSpeed*deltaTime;
    }
    else if(bowlDisplacement >= maxAmountToMoveBowl && moveBowl == 1){
        bowlMovingOut = false;
        bowlPosition.x -= bowlSpeed*deltaTime;
    }
    else if(bowlDisplacement >= maxAmountToMoveBowl && moveBowl == 2){
        bowlMovingOut = false;
        bowlPosition.x += bowlSpeed*deltaTime;
    }
    else if(bowlDisplacement < maxAmountToMoveBowl && bowlPosition.x > bowlStartPosition.x && moveBowl == 1){
        bowlPosition.x -= bowlSpeed*deltaTime;
    }
    else if(bowlDisplacement < maxAmountToMoveBowl && bowlPosition.x < bowlStartPosition.x && moveBowl == 2){
        bowlPosition.x += bowlSpeed*deltaTime;
    }
    else{
        bowlPosition.x = bowlStartPosition.x;
        maxAmountToMoveBowl = 0.0f;
        moveBowl = 0;
        bowlMovingOut = true;
    }



    // Reset maxAmountToMoveBowl and moveBowl both to 0
    // Reset moveBowlOut to true

}

/*
 React to user tap if they hit the left or right arrow keys
 */
void MinigameLogic_1::reactTap(const int &hitOutcome, const bool &isRightTap){
    // Set the direction to move the bowl
    if(isRightTap){
        // moveBowl set to one means move the bowl right and then back to center
        this->moveBowl = 1;
    }
    else{
        // moveBowl set to one means move the bowl left and then back to center
        this->moveBowl = 2;
    }

    // Set the amount to move the bowl (better hits moves the bowl farther
    if(hitOutcome == 0){
        this->maxAmountToMoveBowl = 0;
    }
    else if(hitOutcome == 1){
        this->maxAmountToMoveBowl = 300.0f;
    }
    else if(hitOutcome == 2){
        this->maxAmountToMoveBowl = 150.0f;
    }
    else{
        this->maxAmountToMoveBowl = 50.0f;
    }
}