#include "MinigameLogic_4.h"

MinigameLogic_4::MinigameLogic_4(std::shared_ptr<Song> song)
{
	this->song = song;
	float iter = 0.25f;

	// Create default beat boxes for the entire song of timings from the start
	timings = song->getAllTimings();
	std::shared_ptr<BeatBoxLogic> beat_box;
	// sf::Vector2f startPos, sf::Vector2f endPos, sf::Vector2f postHitPos, sf::Vector2f velocity, float songTimeHit
	for (float time : timings)
	{
		if(iter >=1.25) iter = 0.25f;
		if(iter==0.75f)
		{
			beat_box = std::make_shared<BeatBoxLogic>(sf::Vector2f(300.0f*iter+750.0f, 800.0f), sf::Vector2f(300.0f*iter + 750.0f, 100.0f), sf::Vector2f(300.0f*iter + 750.0f, 34.0f),
			velocity, time);
			beatBoxes.push_back(beat_box);
			beat_box = std::make_shared<BeatBoxLogic>(sf::Vector2f(300.0f*(iter+0.25f)+750.0f, 800.0f), sf::Vector2f(300.0f*(iter+0.25f) + 750.0f, 100.0f), sf::Vector2f(300.0f*iter + 750.0f, 34.0f),
			velocity, time);
			beatBoxes.push_back(beat_box);
		}
		else
			beat_box = std::make_shared<BeatBoxLogic>(sf::Vector2f(300.0f*iter+750.0f, 800.0f), sf::Vector2f(300.0f*iter + 750.0f, 100.0f), sf::Vector2f(300.0f*iter + 750.0f, 34.0f),
			velocity, time);
		beatBoxes.push_back(beat_box);
		iter+=0.25f;
	}
}

void MinigameLogic_4::updateBeatBoxes(const float &deltaTime)
{
	float curSongTime = song->getSongTime();
	std::vector<std::shared_ptr<BeatBoxLogic>> temp;
	int count = 0;
	for (std::shared_ptr<BeatBoxLogic> beatBox : beatBoxes)
	{
		bool canWeMakeIt = beatBox->update(deltaTime, curSongTime);
		if (canWeMakeIt == false)
		{
			std::cout << "Beat box #: " << count
					  << " can't make it in time :(. Consider increasing the speed of the boxes or adjusting another parameter."
					  << std::endl;
		}
		temp.push_back(beatBox);
		count++;
	}
	this->beatBoxes = temp;
}

void MinigameLogic_4::setScore(const int& tapCheck)
{
	switch(tapCheck)
	{
		//miss
		case 3: this->score-=500; break;
		//almost
		case 2: this->score+=200; break;
		//perfect!
		case 1: this->score+=400; break;
	}
}