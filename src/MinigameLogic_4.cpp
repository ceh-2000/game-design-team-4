#include "MinigameLogic_4.h"

MinigameLogic_4::MinigameLogic_4(std::shared_ptr<Song> song)
{
	this->song = song;
	float iter = 0.25f;
	int x1;
	int x2;
	int x3;
	int x4;

	// Create default beat boxes for the entire song of timings from the start
	timings = song->getAllTimings();
// sf::Vector2f startPos, sf::Vector2f endPos, sf::Vector2f postHitPos, sf::Vector2f velocity, float songTimeHit
	for (float time : timings)
	{
		if(iter==1.25f)
			iter = 0.25f;
		if(iter==0.75f)
		{
			beatBoxes.push_back(BeatBoxLogic(sf::Vector2f(300.0f*iter+750.0f, 800.0f), sf::Vector2f(300.0f*iter + 750.0f, 100.0f), sf::Vector2f(300.0f*iter + 750.0f, 50.0f),
										sf::Vector2f(1200.0f, 1200.0f), time));
			beatBoxes.push_back(BeatBoxLogic(sf::Vector2f(300.0f*(iter+0.25f)+750.0f, 800.0f), sf::Vector2f(300.0f*(iter+0.25f) + 750.0f, 100.0f), sf::Vector2f(300.0f*iter + 750.0f, 50.0f),
										sf::Vector2f(1200.0f, 1200.0f), time));
		}
		else
			beatBoxes.push_back(BeatBoxLogic(sf::Vector2f(300.0f*iter+750.0f, 800.0f), sf::Vector2f(300.0f*iter + 750.0f, 100.0f), sf::Vector2f(300.0f*iter + 750.0f, 50.0f),
							sf::Vector2f(1200.0f, 1200.0f), time));
		iter+=0.25f;
	}
}

void MinigameLogic_4::updateBeatBoxes(const float &deltaTime)
{
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