#include "MinigameLogic_3.h"

MinigameLogic_3::MinigameLogic_3(std::shared_ptr<Song> song)
{
    this->song = song;

	// Create default beat boxes for the entire song of timings from the start
    std::vector<float> trueCuts = song->getAllTimings();

    for (float time : trueCuts) {
        beatBoxes.push_back(BeatBoxLogic(sf::Vector2f(-150, 400),
                                         sf::Vector2f(525, 400),
                                         sf::Vector2f(525, 400),
                                         sf::Vector2f(-500.0f, -500.0f), time));
    }

    knifePos = sf::Vector2f(600,600);
	ingredientDim = sf::Vector2f(150, 75);
}

void MinigameLogic_3::update(const float& dt){
	//MinigameLogic::updateBeatBoxes(dt);
}


// void MinigameLogic_3::pushTiming(){
// 	playerCuts.push_back(song->getSongTime());

// }

void MinigameLogic_3::updateBeatBoxes(const float &deltaTime) {
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