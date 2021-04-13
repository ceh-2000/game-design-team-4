#pragma once
#ifndef MINIGAME_LOGIC_2
#define MINIGAME_LOGIC_2
#include "MinigameLogic.h"
class MinigameLogic_2
{
private:
	std::shared_ptr<Song> song;
	float pizzaRadius;
	float spinSpeed;
	std::vector<float> trueAngles;
	std::vector<float> playerAngles;
	sf::Vector2f position;

public:
	MinigameLogic_2(std::shared_ptr<Song> song);
	void move(const float& dt);

	sf::Vector2f getChefPos() { return position; }
	void setChefPos(sf::Vector2f &pos) { position = pos; }
	void setingredientDim(float &a, float &b) { position = sf::Vector2f(a,b); }

	float getPRadius() { return pizzaRadius; }
	void setPRadius(float p) { pizzaRadius = p; }
	
	float getSpinSpeed() { return spinSpeed; }
	void setSpinSpeed(float s) { spinSpeed = s; }

	std::vector<float> getTrueAngles() { return trueAngles; }
	std::vector<float> getPlayerAngles() { return playerAngles; }

};
#endif