#include "Game.h"

Game::Game()
{
	std::vector<std::string> songList;

	// TODO: Push more than one song and allow for rotating between songs
	songList.push_back("../data/music/Sixty_BPM.wav");

	std::shared_ptr<Song> song = std::make_shared<Song>(songList);

	logic = std::make_shared<MinigameLogic>(song);
    view = std::make_shared<MinigameView>(logic, app);


	//logic_1 = std::make_shared<MinigameLogic_1>(song);
	logic_2 = std::make_shared<MinigameLogic_2>(song, 10); //pass maximum cuts allowed
	logic_2->setPosition(sf::Vector2f(app->getSize().x/2.f, app->getSize().y/2.f));
	// std::shared_ptr<MinigameLogic_3> logic_3 = std::make_shared<MinigameLogic_3>(song);
	// std::shared_ptr<MinigameLogic_4> logic_4 = std::make_shared<MinigameLogic_4>(song);

	//view_1 = std::make_shared<MinigameView_1>(logic_1, app);
	view_2 = std::make_shared<MinigameView_2>(logic_2, app);
	// std::shared_ptr<MinigameView_3> view_3 = std::make_shared<MinigameView_3>(logic_3, app);
	// std::shared_ptr<MinigameView_4> view_4 = std::make_shared<MinigameView_4>(logic_4, app);

	// Minigames.push_back(view_1);
	// Minigames.push_back(view_2);
	// Minigames.push_back(view_3);
	// Minigames.push_back(view_4);

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
			this->isActive = false;
			break; // Exit
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				// TODO: Call tapCheck on individual minigame logic
				//logic->tapCheck();
				logic_2->pushNewCut(); //no hit accuracy checking, scoring at end of game
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
	checkEvent();
	//view->update(deltaTime);

	// TODO: make a round subloop for the minigame loops
	// view_1->update(deltaTime)

	//UNCOMMENT FOLLOWING TWO LINES TO RUN PIZZA GAME
	logic_2->update(deltaTime);
	view_2->update(deltaTime);

}
