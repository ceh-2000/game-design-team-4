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

	sf::Texture texture;
	sf::IntRect arrowTextureRect = sf::IntRect(0,0,64,64);

	std::shared_ptr<sf::Sprite> arrow;
	std::vector<std::shared_ptr<sf::Sprite>> arrow_list;
	std::vector<sf::Sprite> endPoints;
	std::vector<sf::Sprite> tables;

	sf::Sprite chef;
	sf::Sprite chef_2;
	sf::Sprite oven;
	sf::Sprite refrigerator;
	sf::Sprite counter;
	sf::Sprite stove;
	sf::RectangleShape backBoard;

	sf::Text score = sf::Text("Score: 0", font, 30);
	sf::Font font;
	int left = 128;
	float elapsedTime = 0;

public:
	MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app);
	void reachInput(const int& input, const int& tapOutcome);
	void resetSprites();
	void updateBeatBoxes(std::vector<BeatBoxLogic> &beatBoxes);
	void draw();
	void update(const float& dt);
};
#endif