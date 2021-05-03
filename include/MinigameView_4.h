#pragma once
#ifndef MINIGAME_VIEW_4
#define MINIGAME_VIEW_4
#include "MinigameView.h"
#include "MinigameLogic_4.h"
#include "Animation.h"

class MinigameView_4
{
private:
	std::shared_ptr<sf::RenderWindow> app;
	std::shared_ptr<MinigameLogic_4> miniLogic;

	sf::Texture texture;
	sf::IntRect arrowTextureRect = sf::IntRect(0, 0, 64, 64);

	std::vector<sf::Sprite> endPoints;
	std::vector<sf::Sprite> tables;

	std::shared_ptr<sf::Sprite> arrow;
	sf::Sprite chef;
	sf::Sprite oven;
	sf::Sprite refrigerator;
	sf::Sprite counter;
	sf::Sprite stove;
	sf::RectangleShape backBoard;
	sf::RectangleShape placeholder;	
	sf::Text score = sf::Text("Score: 0", font, 30);
	sf::Font font;

	int left = 64;


	sf::Texture satsanaTexture;
	sf::Sprite satsanaSprite;
	std::shared_ptr<Animation> satsanaAnimation;
	sf::Text outcome;
	std::string outcomes[4][4] = {{"Try again!", "Perfect!", "Almost!", "Try again!"},
							{"Are you doing that right?", "Looks great!", "Not too bad.", "Are you doing that right?"},
							{"My readers will hear about this!", "Textbook!", "Interesting way of doing that...", "My readers will hear about this!"},
							{"This is a disaster!", "Amazing!", "I could do better!", "This is a disaster!"}};


public:
	MinigameView_4(std::shared_ptr<MinigameLogic_4> MinigameLogic_4, std::shared_ptr<sf::RenderWindow> app);
	void reachInput(const int& input, const int& tapOutcome);
	void updateBeatBoxes(std::vector<BeatBoxLogic> beatBoxes);
	void draw();
	void update(const float& dt);
	void animatePostHit(const int& hitOutcome, int round, const float& deltaTime);
};
#endif