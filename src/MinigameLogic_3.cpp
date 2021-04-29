#include "MinigameLogic_3.h"

MinigameLogic_3::MinigameLogic_3(std::shared_ptr<Song> song)
{
    this->song = song;

	// Create default beat boxes for the entire song of timings from the start
    std::vector<float> trueCuts = song->getAllTimings();

    for (float time : trueCuts) {
        beatBoxes.push_back(BeatBoxLogic(sf::Vector2f(-225, 400),
                                         sf::Vector2f(500, 400),
                                         sf::Vector2f(1275, 400),
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

        if(beatBox.getCurPos().x > 600){
            passedBoxes.push_back(beatBox);
        }
        else{
            temp.push_back(beatBox);
            count++;
        }
    
    }
    this->beatBoxes = temp;

}

void MinigameLogic_3::updateOthers(const float& deltaTime){
    float curSongTime = song->getSongTime();

     for (BeatBoxLogic beatBox : this->cutBoxes) {
        bool canWeMakeIt = beatBox.update(deltaTime, curSongTime);
    }

    for (BeatBoxLogic beatBox : this->passedBoxes) {
        bool canWeMakeIt = beatBox.update(deltaTime, curSongTime);
    }
}

void MinigameLogic_3::updateScore(const int &hitOutcome, bool regionCheck){
    if(hitOutcome == 0) this->score += this->badTapBoost;
    if(hitOutcome == 1) this->score += this->goodTapBoost;
    if(hitOutcome == 2) this->score += this->almostTapBoost;
    if(hitOutcome == 3) this->score += this->badTapBoost;

    if(!regionCheck) this->score += this->badTapBoost;

}