#pragma once
#ifndef MINIGAME_VIEW_3
#define MINIGAME_VIEW_3
#include "MinigameView.h"
#include "MinigameLogic_3.h"
<<<<<<< Updated upstream
class MinigameView_3 : public MinigameView
=======
#include "Animation.h"

class MinigameView_3
>>>>>>> Stashed changes
{
private:
	std::shared_ptr<MinigameLogic> miniLogic;
	sf::Sprite vegetable;
	std::vector<sf::RectangleShape> actualCuts;
	std::vector<sf::RectangleShape> playerCuts;
<<<<<<< Updated upstream
	
public:
	MinigameView_3(std::shared_ptr<MinigameLogic> MinigameLogic_3);
	void draw(std::shared_ptr<sf::RenderWindow> window);
=======

	sf::RectangleShape knifeBox;

	Animation animation;

	bool move = false;


	
public:
	MinigameView_3(std::shared_ptr<MinigameLogic_3> MinigameLogic_3, std::shared_ptr<sf::RenderWindow> app);
	void draw();
	void update(const float& deltaTime);
	void updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes);
	void splitBox(const float& deltaTime);

>>>>>>> Stashed changes
};
MinigameView_3::MinigameView_3(std::shared_ptr<MinigameLogic> MinigameLogic_3) : MinigameView(MinigameLogic_3)
{
	this->miniLogic = MinigameLogic_3;
}
#endif