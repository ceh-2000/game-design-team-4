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

	sf::Vector2f blockSize = sf::Vector2f(64.0f, 64.0f);
	sf::Texture texture;
	sf::IntRect arrowTextureRect = sf::IntRect(0, 0, 64, 64);

	std::vector<sf::Sprite> endPoints;
	std::vector<sf::Sprite> tables;

	//TODO: Replace RectangleShapes with art
	sf::Sprite chef;
	sf::Sprite oven;
	sf::Sprite refrigerator;
	sf::Sprite counter;
	sf::Sprite stove;
	
	sf::Text score = sf::Text("", font, 30);
	sf::Font font;

public:
	MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app);
	void resetInput();
	void reachInput(const int& input, const int& tapOutcome);
	void updateBeatBoxes(std::vector<std::shared_ptr<BeatBoxLogic>> beatBoxes);
	void draw();
	void update(const float& dt);
};
#endif