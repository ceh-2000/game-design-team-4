#include "MinigameLogic.h"

MinigameLogic::MinigameLogic(std::shared_ptr<Song> song) {
    this->song = song;
    this->elapsedDuration = this->duration;
}

/*
Start the game by starting the song
*/
void MinigameLogic::startGame() {
    song->play();
}

/*
Gets the previous hit given a song time
*/
float MinigameLogic::determinePrevTap(float songTime) {
    if (tapNum == 0) {
        return song->getACorrectTiming(tapNum);
    }
    return song->getACorrectTiming(tapNum - 1);
}

/*
Gets the next hit given a song time
*/
float MinigameLogic::determineNextTap(float songTime) {
    float nextTap = song->getACorrectTiming(tapNum);
    if (std::abs(nextTap - 50000) < 0.01) {
        return nextTap;
    }
    while (songTime > nextTap) {
        tapNum = tapNum + 1;
        nextTap = song->getACorrectTiming(tapNum);
    }
    return nextTap;
}

/*
Check whether or not user tapped at all
*/
int MinigameLogic::tapCheck() {
    float curSongTime = song->getSongTime();
    float nextTap = determineNextTap(curSongTime);
    float prevTap = determinePrevTap(curSongTime);

    std::cout << "current to nextTap: " << std::abs(curSongTime - nextTap) << std::endl;
    std::cout << "current to prevTap: " << std::abs(curSongTime - prevTap) << std::endl;

    // Current song time not in any tap action regions
    if ((std::abs(curSongTime - nextTap) > actRegion && std::abs(curSongTime - prevTap) > actRegion)) {
        isHit = false;
        backgroundColor = 0;
    }

    // Current song time hit in success range
    else if (std::abs(curSongTime - nextTap) < winRegion || std::abs(curSongTime - prevTap) < winRegion) {
        std::cout << "Hit!" << std::endl;
        backgroundColor = 1;
        isHit = true;
        animate = true;
        // resultText.setString("Perfect!");
    }

    // Current song time hit in almost range
    else if (std::abs(curSongTime - nextTap) > winRegion && std::abs(curSongTime - prevTap) < almostRegion ||
             std::abs(curSongTime - nextTap) < winRegion && std::abs(curSongTime - prevTap) > almostRegion) {
        std::cout << "Almost!" << std::endl;
        backgroundColor = 2;
        isHit = true;
        animate = true;
        // resultText.setString("Almost!");
    }

    // Current song time hit in fail range
    else {
        std::cout << "Miss!" << std::endl;
        backgroundColor = 3;
        isHit = true;
        animate = true;
        // resultText.setString("Try Again!");
    }

    return backgroundColor;
}

/*
Check whether the player did not tap in previous action region
*/
void MinigameLogic::regionCheck() {
    float curSongTime = song->getSongTime();
    float nextTap = determineNextTap(curSongTime);
    float prevTap = determinePrevTap(curSongTime);

    // Kick-off an animation to show that the user missed because they never hit
    if (!isHit && (std::abs(curSongTime - nextTap) > actRegion && std::abs(curSongTime - prevTap) > actRegion)) {
        std::cout << "No tap in action region" << std::endl;
        std::cout << "Miss!" << std::endl;
        backgroundColor = 3;
        isHit = true;
        animate = true;
        // resultText.setString("Try Again!");
        resetHitYet = false;
    } else if ((std::abs(curSongTime - nextTap) > actRegion && std::abs(curSongTime - prevTap) > actRegion)) {
        resetHitYet = false;
    }
        // Reset once we reenter an active region
    else if (resetHitYet == false && std::abs(curSongTime - nextTap) < actRegion) {
        isHit = false;
        resetHitYet = true;
    }
}

// Handle animations changes post hit
void MinigameLogic::updatePostHit(const float &deltaTime) {
    if (animate) {
        this->elapsedDuration += deltaTime;

        while (this->elapsedDuration > this->duration) {
            this->elapsedDuration -= this->duration;

            // TODO: Update current sprite frame in view
            // if (rectSourceSprite.left == 256)
            // {
            // 	rectSourceSprite.left = 0;
            // }
            // else
            // {
            // 	rectSourceSprite.left += 128;
            // }

            counter++;
            if (counter == 6) {
                animate = false;
                backgroundColor = 0;
                counter = 0;

                // TODO: Update current text in view
                // resultText.setString("");
            }
        }
        // TODO: Update current sprite in view
        // sprite.setTextureRect(rectSourceSprite);
    }

}