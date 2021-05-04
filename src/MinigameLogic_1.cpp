#include "MinigameLogic_1.h"

MinigameLogic_1::MinigameLogic_1(std::shared_ptr<Song> song, float x, float y) {
    this->song = song;
    this->windowSize = sf::Vector2f(x, y);
    this->distanceToBowl = y * 0.75;
    this->bowlPosition = sf::Vector2f(x / 2.0f - bowlSize.x, distanceToBowl - bowlSize.y);
    this->bowlStartPosition = this->bowlPosition;

    // Create default beat boxes for the entire song of timings from the start
    std::vector<float> allSongTimings = song->getAllTimings();
    for (float time : allSongTimings) {
        float LO = 0.0f;
        float HI = 1.0f;
        float randomNum1 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
        float randomNum2 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

        float startX = windowSize.x / 2 + 100;
        if (randomNum1 < 0.5) {
            startX = windowSize.x / 2 - 100;
        }

        if (randomNum2 < 0.5) {
            isGoodVector.push_back(false);
        } else {
            isGoodVector.push_back(true);
        }

        beatBoxes.emplace_back(sf::Vector2f(startX, -ingredientDim.y),
                               sf::Vector2f(startX, distanceToBowl - bowlSize.y * 2),
                               sf::Vector2f(startX, distanceToBowl),
                               sf::Vector2f(ingredientSpeed, ingredientSpeed),
                               time);
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

        bool isAtPostHit = beatBox.isAtPostHit();
        if (isAtPostHit) {
            beatBox.setPostHitPos(sf::Vector2f(-100, -100));
            beatBox.setCurPos(sf::Vector2f(-100, -100));
        }

        beatBox.update(deltaTime, curSongTime);

        bool isAtEnd = beatBox.isAtEnd();
        if (isAtEnd) {
            curBeatBoxIndex = count;
        }


        temp.push_back(beatBox);
        count++;
    }
    this->beatBoxes = temp;
}

void MinigameLogic_1::updateBowl(const float &deltaTime) {
    float bowlDisplacement = std::abs(bowlPosition.x - bowlStartPosition.x);

    float bowl_start_pos = bowlStartPosition.x;
    float bowl_cur_pos = bowlPosition.x;
    float bowl_end_pos = bowlStartPosition.x + maxAmountToMoveBowl;
    if (moveBowl == 2) {
        bowl_end_pos = bowlStartPosition.x - maxAmountToMoveBowl;
    }

    // Moving bowl out and to the right; less than max
    if (bowlMovingOut && bowl_cur_pos >= bowl_start_pos && bowl_cur_pos < bowl_end_pos && moveBowl == 1) {
        bowlPosition.x += bowlSpeed * deltaTime;
    }
        // Moving bowl out and to the left; less than max
    else if (bowlMovingOut && bowl_cur_pos <= bowl_start_pos && bowl_cur_pos > bowl_end_pos && moveBowl == 2) {
        bowlPosition.x -= bowlSpeed * deltaTime;
    }
        // Moving bowl in and and from the right; less than max
    else if (!bowlMovingOut && bowl_cur_pos > bowl_start_pos && bowl_cur_pos < bowl_end_pos && moveBowl == 1) {
        bowlPosition.x -= bowlSpeed * deltaTime;
    }
        // Moving bowl in and and from the left; less than max
    else if (!bowlMovingOut && bowl_cur_pos < bowl_start_pos && bowl_cur_pos > bowl_end_pos && moveBowl == 2) {
        bowlPosition.x += bowlSpeed * deltaTime;
    }
        // Moving bowl in and and from the right; beyond max
    else if (bowl_cur_pos >= bowl_end_pos && moveBowl == 1) {
        bowlMovingOut = false;
        bowlPosition.x -= bowlSpeed * deltaTime;
    }
        // Moving bowl in and and from the left; beyond max
    else if (bowl_cur_pos <= bowl_end_pos && moveBowl == 2) {
        bowlMovingOut = false;
        bowlPosition.x += bowlSpeed * deltaTime;
    }
        // Don't move bowl
    else {
        bowlPosition.x = bowlStartPosition.x;
        maxAmountToMoveBowl = 0.0f;
        moveBowl = 0;
        bowlMovingOut = true;
    }

    // TODO: Reset maxAmountToMoveBowl and moveBowl both to 0
    // TODO: Reset moveBowlOut to true
}

/*
 React to user tap if they hit the left or right arrow keys
 */
void MinigameLogic_1::reactTap(const int &hitOutcome, const bool &isRightTap) {

    // Determine whether the user should tap right or left
    BeatBoxLogic currentBeatBox = beatBoxes.at(curBeatBoxIndex);
    bool isRightCorrect = true;
    if (currentBeatBox.getStartPos().x > windowSize.x) {
        isRightCorrect = false;
    }

    // Determine whether the ingredient is good or not
    bool isGood = true;
    if (!isGoodVector.at(curBeatBoxIndex)) {
        isGood = false;
    }

    // Set the amount to move the bowl (better hits moves the bowl farther
    if (hitOutcome == 0) {
        this->maxAmountToMoveBowl = 0;
    } else if (hitOutcome == 1){ // and moveBowl == 0) {
        this->maxAmountToMoveBowl = 300.0f;
        // Case where we move the right direction out of the way of a bad ingredient
        if (!isGood && (isRightCorrect == isRightTap)) {
            this->score += this->goodTapBoost;
            std::cout << "CORRECT DIRECTION" << std::endl;

        }
            // Case where we move the wrong direction out of the way of a bad ingredient
        else if (!isGood) {
            this->score += this->badTapBoost;
            std::cout << "PLAYER MOVED THE WRONG WAY" << std::endl;
        }
        std::cout << "GOOD HIT" << std::endl;

        // Do nothing if they move out of the way of a good ingredient
    } else if (hitOutcome == 2){ // moveBowl == 0) {
        this->maxAmountToMoveBowl = 150.0f;
        // Regardless of good or bad ingredient just provide the almost tap boost
        this->score += this->almostTapBoost;
    } else if (hitOutcome == 3){ // and moveBowl == 0) {
        this->maxAmountToMoveBowl = 50.0f;
        // Case where we want to accept a good ingredient, so we get bonus points for a miss :)
        if (isGood) {
            this->score += this->goodTapBoost;
        }
            // Case where we missed an accepted a bad ingredient
        else {
            this->score += badTapBoost;
        }
    }

    // Set the direction to move the bowl
    if (isRightTap) {
        // moveBowl set to one means move the bowl right and then back to center
        this->moveBowl = 1;
    } else {
        // moveBowl set to one means move the bowl left and then back to center
        this->moveBowl = 2;
    }

}

void MinigameLogic_1::noTap(const bool &didHit) {
    // Determine if it's ok that user didn't tap or they should have...
    if (!didHit && !firstTapScore) {
        if (isGoodVector.at(curBeatBoxIndex)) {
            score += this->goodTapBoost;
        } else {
            // Extra punishment for not moving
            score -= this->goodTapBoost;
        }
    }

    // Handle problem double-scoring the first box if no tap in action region
    firstTapScore = false;
}

std::string MinigameLogic_1::gradeMinigame() {
    //calculate max score for percent out of 100
    float maxScore = this->goodTapBoost * beatBoxes.size();
    float grade = 100.f * score / maxScore;

    std::string letter_grade = " ";
    if (grade > 95) {
        letter_grade = "S";
    } else if (grade > 90) {
        letter_grade = "A";
    } else if (grade > 80) {
        letter_grade = "B";
    } else if (grade > 70) {
        letter_grade = "C";
    } else if (grade > 60) {
        letter_grade = "D";
    } else letter_grade = "F";
    this->grade = letter_grade;
    return this->grade;
}

void MinigameLogic_1::update(const float &deltaTime, const bool &didHit) {
    this->noTap(didHit);
    this->updateBeatBoxes(deltaTime);
    this->updateBowl(deltaTime);
}
