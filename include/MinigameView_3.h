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
	sf::Sprite vegetable;
	sf::Sprite knife;
	
	std::vector<sf::RectangleShape> actualCuts;
	std::vector<sf::RectangleShape> playerCuts;

	sf::RectangleShape knifeBox;

	bool move = false;

	sf::Texture satsanaTexture;
	sf::Sprite satsanaSprite;

	std::shared_ptr<Animation> animation;


	
public:
	MinigameView_3(std::shared_ptr<MinigameLogic_3> MinigameLogic_3, std::shared_ptr<sf::RenderWindow> app);

	void draw();
	void update(const float& deltaTime);
	void updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes);
	void splitBox(const float& deltaTime);
};

#endif