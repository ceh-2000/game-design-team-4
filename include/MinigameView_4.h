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
	std::vector<sf::RectangleShape> tables;
	//TODO: Replace RectangleShapes with art
	// sf::Sprite chef;
	// sf::Sprite oven;
	// sf::Sprite refrigerator;
	// sf::Sprite counter;
	// sf::Sprite stove;
	sf::Vector2f blockSize = sf::Vector2f(50.0f,50.0f);
	//Placeholder rectShapes
	sf::RectangleShape chef = sf::RectangleShape(blockSize);
	sf::RectangleShape oven = sf::RectangleShape(blockSize);
	sf::RectangleShape refrigerator = sf::RectangleShape(blockSize);
	sf::RectangleShape counter = sf::RectangleShape(blockSize);
	sf::RectangleShape stove = sf::RectangleShape(blockSize);
	bool resetInputs = false;

	
public:
	MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app);
	void resetInput();
	void reachInput(const int& input, const int& tapOutcome);
	void updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes);
	void draw();
	void update(const float& dt);
};
#endif