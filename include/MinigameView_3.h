#pragma once
#ifndef MINIGAME_VIEW_3
#define MINIGAME_VIEW_3
#include "MinigameView.h"
#include "MinigameLogic_3.h"
#include "Animation.h"
class MinigameView_3
{
private:
	std::shared_ptr<sf::RenderWindow> app;
	std::shared_ptr<MinigameLogic_3> miniLogic;
	sf::Texture sushiTexture;
	sf::Texture cutSushiTexture;
	
	sf::Texture knifeTexture;
	sf::Sprite knifeSprite;
	
	std::vector<sf::RectangleShape> actualCuts;
	std::vector<sf::RectangleShape> playerCuts;

	sf::RectangleShape knifeBox;

	bool move = false;
	bool moving = false;

	sf::Texture satsanaTexture;
	sf::Sprite satsanaSprite;

	sf::Texture beltTexture;
	sf::Sprite beltSprite;

	std::shared_ptr<Animation> animation;
	std::shared_ptr<Animation> beltAnimation;

	sf::Font font;
	sf::Text scoreText;

	sf::Text outcome;

	std::string outcomes[4][4] = {{"Try again!", "Perfect!", "Almost!", "Try again!"},
							{"Are you doing that right?", "Looks great!", "Not too bad.", "Are you doing that right?"},
							{"My readers will hear about this!", "Textbook!", "Interesting way of doing that...", "My readers will hear about this!"},
							{"This is a disaster!", "Amazing!", "I could do better!", "This is a disaster!"}};


	
public:
	MinigameView_3(std::shared_ptr<MinigameLogic_3> MinigameLogic_3, std::shared_ptr<sf::RenderWindow> app);

	void draw(const float& deltaTime);
	void update(const float& deltaTime);
	void updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes, const std::vector<BeatBoxLogic> &passedBoxes, const std::vector<BeatBoxLogic> &cutBoxes);
	void splitBox(const float& deltaTime);
	void animatePostHit(const int& hitOutcome, int round, const float& deltaTime);
};
#endif