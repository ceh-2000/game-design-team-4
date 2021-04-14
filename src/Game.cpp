#include "Game.h"

Game::Game()
{
	std::vector<std::string> songList;

	// TODO: Push more than one song and allow for rotating between songs
	songList.push_back("../data/music/Sixty_BPM.wav");

	std::shared_ptr<Song> song = std::make_shared<Song>(songList);

	logic = std::make_shared<MinigameLogic>(song);
    view = std::make_shared<MinigameView>(logic, app);


	// logic_3 = std::make_shared<MinigameLogic_3>(song);
	// std::shared_ptr<MinigameLogic_2> logic_2 = std::make_shared<MinigameLogic_2>(song);
	// std::shared_ptr<MinigameLogic_3> logic_3 = std::make_shared<MinigameLogic_3>(song);
	logic_4 = std::make_shared<MinigameLogic_4>(song);

	// view_3 = std::make_shared<MinigameView_3>(logic_3, app);
	// std::shared_ptr<MinigameView_2> view_2 = std::make_shared<MinigameView_2>(logic_2, app);
	// std::shared_ptr<MinigameView_3> view_3 = std::make_shared<MinigameView_3>(logic_3, app);
	view_4 = std::make_shared<MinigameView_4>(logic_4, app);
}

// General game loop stays
void Game::checkEvent(const float &deltaTime)
{
	// Process events
	sf::Event event;
	while (app->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->isActive = false;
			break; // Exit
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				// TODO: Call tapCheck on individual minigame logic
				logic->tapCheck();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void Game::update(const float &deltaTime)
{
    app->clear();
	checkEvent(deltaTime);

	// TODO: make a round subloop for the minigame loops
	view->update(deltaTime);
    view_4->update(deltaTime);
    view->draw();

}