#include "MinigameLogic_3.h"

MinigameLogic_3::MinigameLogic_3(std::shared_ptr<Song> song, int round) {
    this->song = song;

    switch (round) {
      case 0:
        this->velocity = sf::Vector2f(-700, -700);
        break;
      case 1:
       this->velocity = sf::Vector2f(-800, -800);
        break;
      case 2:
        this->velocity = sf::Vector2f(-900, -900);
        break;
      case 3:
        this->velocity = sf::Vector2f(-1000, -1000);
        break;
      default:
        break;
    }

    // Create default beat boxes for the entire song of timings from the start
    std::vector<float> trueCuts = song->getAllTimings();


    for (float time : trueCuts) {
        beatBoxes.push_back(BeatBoxLogic(sf::Vector2f(-225, 500),
                                         sf::Vector2f(500, 500),
                                         sf::Vector2f(1275, 500),
                                         velocity, time));
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

    for (BeatBoxLogic beatBox : beatBoxes) {
        bool canWeMakeIt = beatBox.update(deltaTime, curSongTime);
        //bool isDone = beatBox.isAtEnd();
        sf::Vector2f endPos = beatBox.getEndPos();
        curBeatBoxIndex = count;

        if (endPos.x - 20 <= beatBox.getCurPos().x && beatBox.getCurPos().x <= beatBox.getCurPos().x + 20 &&
            needToSplit) {
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

        } else if (beatBox.getCurPos().x > endPos.x + 200 && !needToSplit) {
            passedBoxes.push_back(BeatBoxLogic(beatBox.getCurPos(),
                                               beatBox.getPostHitPos(),
                                               beatBox.getPostHitPos(),
                                               beatBox.getVelocity(),
                                               beatBox.getSongTime() + .5));
        } else {
            //keep going
            temp.push_back(beatBox);
        }

        count++;
    }

    this->beatBoxes = temp;
}

void MinigameLogic_3::updateCut(const float &deltaTime) {
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

void MinigameLogic_3::updatePassed(const float &deltaTime) {
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

std::string MinigameLogic_3::gradeMinigame() {
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

void MinigameLogic_3::updateScore(const int &hitOutcome, bool regionCheck) {
    if (hitOutcome == 0) this->score += this->badTapBoost;
    if (hitOutcome == 1) this->score += this->goodTapBoost;
    if (hitOutcome == 2) this->score += this->almostTapBoost;
    if (hitOutcome == 3) this->score += this->badTapBoost;

    if (!regionCheck) this->score += this->badTapBoost;

    if(hitOutcome == 1){
        needToSplit = true;
    }

}
