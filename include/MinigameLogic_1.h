#pragma once
#ifndef MINIGAME_LOGIC_1
#define MINIGAME_LOGIC_1
#include "MinigameLogic.h"
class MinigameLogic_1 : public MinigameLogic
{
private:
	sf::Vector2f ingredientDim;
	sf::Vector2f position;
	float ingredientSpeed;
	float distanceToBowl;

public:
	MinigameLogic_1(std::shared_ptr<Song> song, std::shared_ptr<sf::RenderWindow> app);
	void move(const float& dt);

	sf::Vector2f getIngredDim() { return ingredientDim; }
	void setIngredDim(sf::Vector2f& dim) { ingredientDim = dim;}
	void setIngredDim(float& a, float& b) { ingredientDim = sf::Vector2f(a,b); }

	sf::Vector2f getChefPos() { return position; }
	void setChefPos(sf::Vector2f &pos) { position = pos; }
	void setingredientDim(float &a, float &b) { position = sf::Vector2f(a,b); }

	float getIngredSpeed() { return ingredientSpeed; }
	void setIngredSpeed(float s) { ingredientSpeed = s; }

	float getDist() { return distanceToBowl; }
	void setDist(float d) { distanceToBowl = d; }
};
MinigameLogic_1::MinigameLogic_1(std::shared_ptr<Song> song, std::shared_ptr<sf::RenderWindow> app) : MinigameLogic(song, app){}
#endif