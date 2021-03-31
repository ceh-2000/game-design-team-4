#pragma once
#ifndef MINIGAME_LOGIC_4
#define MINIGAME_LOGIC_4
#include "MinigameLogic.h"
class MinigameLogic_4 : public MinigameLogic
{
private:
	sf::Vector2f chefDim;
	sf::Vector2f chefPosition;
	float chefSpeed;
	std::vector<std::vector<float>> arrowKeys;

public:
	MinigameLogic_4(/* args */);
	void move(const float& dt);

	sf::Vector2f getChefDim() { return chefDim; }
	void setChefDim(sf::Vector2f& dim) { chefDim = dim;}
	void setChefDim(float& a, float& b) { chefDim = sf::Vector2f(a,b); }

	sf::Vector2f getChefPos() { return chefPosition; }
	void setChefPos(sf::Vector2f &pos) { chefPosition = pos; }
	void setChefDim(float &a, float &b) { chefPosition = sf::Vector2f(a,b); }

	float getChefSpeed() { return chefSpeed; }
	void setChefSpeed(float s) { chefSpeed = s; }

	std::vector<std::vector<float>> getArrowKeys() { return arrowKeys; }
};
MinigameLogic_4::MinigameLogic_4(/* args */){}
#endif