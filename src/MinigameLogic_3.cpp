#include "MinigameLogic_3.h"

MinigameLogic_3::MinigameLogic_3(std::shared_ptr<Song> song) {
    this->song = song;

    // Create default beat boxes for the entire song of timings from the start
    std::vector<float> trueCuts = song->getAllTimings();

    for (float time : trueCuts) {
        beatBoxes.push_back(BeatBoxLogic(sf::Vector2f(-225, 400),
                                         sf::Vector2f(500, 400),
                                         sf::Vector2f(1275, 400),
                                         sf::Vector2f(-500.0f, -500.0f), time));
    }

    knifePos = sf::Vector2f(600, 600);
    ingredientDim = sf::Vector2f(150, 75);


}

void MinigameLogic_3::update(const float &dt) {
    //MinigameLogic::updateBeatBoxes(dt);
}


void MinigameLogic_3::updateBeatBoxes(const float &deltaTime) {
    float curSongTime = song->getSongTime();
    std::vector<BeatBoxLogic> temp;
    int count = 0;

    for (BeatBoxLogic beatBox : beatBoxes){
        bool canWeMakeIt = beatBox.update(deltaTime, curSongTime);
        //bool isDone = beatBox.isAtEnd();
        sf::Vector2f endPos = beatBox.getEndPos();
        curBeatBoxIndex = count;

            if(endPos.x - 20 <= beatBox.getCurPos().x && beatBox.getCurPos().x <= beatBox.getCurPos().x + 20 && needToSplit){
                sf::Vector2f newRightPos = beatBox.getCurPos();
                sf::Vector2f newLeftPos = beatBox.getCurPos();
                newRightPos.x += 65;
                newLeftPos.x -= 75;
                
                cutBoxes.push_back(BeatBoxLogic(newRightPos,
                                                beatBox.getPostHitPos(),
                                                beatBox.getPostHitPos(),
                                                beatBox.getVelocity(),
                                                beatBox.getSongTime() + .5));

                cutBoxes.push_back(BeatBoxLogic(newLeftPos,
                                                beatBox.getPostHitPos(),
                                                beatBox.getPostHitPos(),
                                                beatBox.getVelocity(),
                                                beatBox.getSongTime() + .5));

                needToSplit = false;

            }

            else if(beatBox.getCurPos().x > endPos.x + 100 && !needToSplit){
                passedBoxes.push_back(BeatBoxLogic(beatBox.getCurPos(),
                                                beatBox.getPostHitPos(),
                                                beatBox.getPostHitPos(),
                                                beatBox.getVelocity(),
                                                beatBox.getSongTime() + .5));
            }
            else {
                //keep going
                temp.push_back(beatBox);
            }

            count++;
        }

    this->beatBoxes = temp;
}

void MinigameLogic_3::updateCut(const float& deltaTime){
    float curSongTime = song->getSongTime();
    std::vector<BeatBoxLogic> temp;
    int count = 0;

     for (BeatBoxLogic beatBox : this->cutBoxes) {
        beatBox.moveX(deltaTime);
        //bool canWeMakeIt = beatBox.update(deltaTime, curSongTime);

        temp.push_back(beatBox);
        count++;
    }
    this->cutBoxes = temp;
}

void MinigameLogic_3::updatePassed(const float& deltaTime){
    float curSongTime = song->getSongTime();
    std::vector<BeatBoxLogic> temp;
    int count = 0;

     for (BeatBoxLogic beatBox : this->passedBoxes) {
        beatBox.moveX(deltaTime);

        temp.push_back(beatBox);
        count++;
    }
    this->passedBoxes = temp;
}

void MinigameLogic_3::updateScore(const int &hitOutcome, bool regionCheck) {
    if (hitOutcome == 0) this->score += this->badTapBoost;
    if (hitOutcome == 1) this->score += this->goodTapBoost;
    if (hitOutcome == 2) this->score += this->almostTapBoost;
    if (hitOutcome == 3) this->score += this->badTapBoost;

    if(!regionCheck) this->score += this->badTapBoost;

    if(hitOutcome == 1 || hitOutcome == 2){
        needToSplit = true;
    }

}
