#pragma once
#ifndef MINIGAME_LOGIC_1
#define MINIGAME_LOGIC_1
#include "MinigameLogic.h"
class MinigameLogic_1
{
private:
	std::shared_ptr<Song> song;
	sf::Vector2f ingredientDim = sf::Vector2f(50.0f, 50.0f);
	float ingredientSpeed = 500.0f;
	float distanceToBowl = 400.0f;
    std::vector<BeatBoxLogic> beatBoxes;
    std::vector<bool> isGoodVector;

    sf::Vector2f bowlPosition;

public:
	MinigameLogic_1(std::shared_ptr<Song> song);
    std::vector<BeatBoxLogic> getBeatBoxes() { return beatBoxes; }
    std::vector<bool> getIsGoodVector() { return isGoodVector; }


    void updateBeatBoxes(const float &deltaTime);

    void move(const float& dt);

    sf::Vector2f getIngredDim() { return ingredientDim; }
	void setIngredDim(sf::Vector2f& dim) { ingredientDim = dim;}

	sf::Vector2f getChefPos() { return bowlPosition; }
	void setChefPos(sf::Vector2f &pos) { bowlPosition = pos; }

};
#endif