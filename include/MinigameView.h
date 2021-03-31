#pragma once
#ifndef MINIGAME_VIEW_H
#define MINIGAME_VIEW_H
#include "Game.h"
#include "MinigameLogic.h"
class MinigameView : std::enable_shared_from_this<MinigameView>
{
private:
	std::shared_ptr<MinigameLogic> minigameLogic;
	sf::Texture background;
	std::vector<std::string> backgroundPaths;
	

public:
	MinigameView(std::shared_ptr<MinigameLogic> minigameLogic);
	virtual void draw(std::shared_ptr<sf::RenderWindow> window) = 0;
};

MinigameView::MinigameView(std::shared_ptr<MinigameLogic> minigameLogic){ this->minigameLogic = minigameLogic; }
#endif