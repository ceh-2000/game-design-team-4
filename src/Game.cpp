#include "Game.h"

Game::Game()
{
	// TODO: Create pointer to individual minigame logic
}

// General game loop stays
void Game::checkEvent()
{
	// Process events
	sf::Event event;
	while (app->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			isActive = false;
			break; // Exit
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				// TODO: Call tapCheck on individual minigame logic
				tapCheck(); 
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void Game::update(const float& deltaTime)
{
	// TODO: Call this update on individual minigame class
	update(deltaTime)
}