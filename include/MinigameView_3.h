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
	sf::Sprite knife;
	
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


	
public:
	MinigameView_3(std::shared_ptr<MinigameLogic_3> MinigameLogic_3, std::shared_ptr<sf::RenderWindow> app);

	void draw(const float& deltaTime);
	void update(const float& deltaTime);
	void updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes, const std::vector<BeatBoxLogic> &passedBoxes, const std::vector<BeatBoxLogic> &cutBoxes);
	void splitBox(const float& deltaTime);
};

#endif