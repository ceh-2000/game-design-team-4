#include "MinigameLogic_1.h"

MinigameLogic_1::MinigameLogic_1(std::shared_ptr<Song> song)
{
    this->song = song;

    // Create default beat boxes for the entire song of timings from the start
    std::vector<float> allSongTimings = song->getAllTimings();
    for (float time : allSongTimings) {
        float LO = 0.0f;
        float HI = 700.0f;

        float randStartX = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

        beatBoxes.push_back(BeatBoxLogic(sf::Vector2f(randStartX, -50), sf::Vector2f(randStartX, 400),
                                         sf::Vector2f(-500.0f, -500.0f), time));
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