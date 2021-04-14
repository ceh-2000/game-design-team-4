#pragma once
#ifndef MINIGAME_VIEW_4
#define MINIGAME_VIEW_4
#include "MinigameView.h"
#include "MinigameLogic_4.h"
class MinigameView_4
{
private:
	std::shared_ptr<sf::RenderWindow> app;
	std::shared_ptr<MinigameLogic_4> miniLogic;
	std::vector<sf::RectangleShape> endPoints;
	sf::Sprite chef;
	sf::Sprite oven;
	sf::Sprite refrigerator;
	sf::Sprite counter;
	sf::Sprite stove;
	
public:
	MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app);
	void updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes);
	void draw();
	void update(const float& dt);
};
#endif