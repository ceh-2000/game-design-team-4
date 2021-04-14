#include "MinigameLogic_1.h"

MinigameLogic_1::MinigameLogic_1(std::shared_ptr<Song> song) {
    this->song = song;

    // Create default beat boxes for the entire song of timings from the start
    std::vector<float> allSongTimings = song->getAllTimings();
    for (float time : allSongTimings) {
        float LO = 0.0f;
        float HI = 1.0f;
        float randomNum1 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
        float randomNum2 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

        float startX = 500;
        if(randomNum1 < 0.5){
            startX = 300;
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