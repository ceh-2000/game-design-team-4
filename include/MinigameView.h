#pragma once
#ifndef MINIGAME_VIEW_H
#define MINIGAME_VIEW_H
#include "Game.h"
#include "MinigameLogic.h"
class MinigameView : std::enable_shared_from_this<MinigameView>
{
protected:
	sf::Texture background;
	std::vector<std::string> backgroundPaths;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectSourceSprite;

    sf::Font font;
    sf::Text resultText;	

public:
	MinigameView();
	virtual void draw(std::shared_ptr<sf::RenderWindow> window) = 0;
};
#endif