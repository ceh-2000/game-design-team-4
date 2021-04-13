#pragma once
#ifndef MINIGAME_LOGIC_3
#define MINIGAME_LOGIC_3
#include "MinigameLogic.h"
class MinigameLogic_3
{
private:
	std::shared_ptr<Song> song;
	sf::Vector2f ingredientDim;
	sf::Vector2f position;
	float ingredientSpeed;
	std::vector<float> trueCuts;
	std::vector<float> playerCuts;

public:
	MinigameLogic_3(std::shared_ptr<Song> song);
	void move(const float& dt);

	sf::Vector2f getIngredDim() { return ingredientDim; }
	void setIngredDim(sf::Vector2f& dim) { ingredientDim = dim;}
	void setIngredDim(float& a, float& b) { ingredientDim = sf::Vector2f(a,b); }

	sf::Vector2f getChefPos() { return position; }
	void setChefPos(sf::Vector2f &pos) { position = pos; }
	void setingredientDim(float &a, float &b) { position = sf::Vector2f(a,b); }

	float getIngredSpeed() { return ingredientSpeed; }
	void setIngredSpeed(float s) { ingredientSpeed = s; }

	std::vector<float> getTrueCuts() { return trueCuts; }
	std::vector<float> getPlayerCuts() { return playerCuts; }


};
#endif