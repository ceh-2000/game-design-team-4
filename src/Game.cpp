#include "Game.h"

Game::Game()
{
	std::vector<std::string> songList;

	// TODO: Push more than one song and allow for rotating between songs
	songList.push_back("../data/music/Sixty_BPM.wav");

	std::shared_ptr<Song> song = std::make_shared<Song>(songList);

	logic = std::make_shared<MinigameLogic>(song);
  view = std::make_shared<MinigameView>(logic, app);



	logic_1 = std::make_shared<MinigameLogic_1>(song);
	logic_2 = std::make_shared<MinigameLogic_2>(song, 10); //pass maximum cuts allowed
	//Position setting should be refactored
	logic_2->setPosition(sf::Vector2f(app->getSize().x/2.f, app->getSize().y/2.f));
	logic_3 = std::make_shared<MinigameLogic_3>(song);
	logic_4 = std::make_shared<MinigameLogic_4>(song);


	view_1 = std::make_shared<MinigameView_1>(logic_1, app);
	view_2 = std::make_shared<MinigameView_2>(logic_2, app);
	view_3 = std::make_shared<MinigameView_3>(logic_3, app);
	view_4 = std::make_shared<MinigameView_4>(logic_4, app);
}

void Game::switchToNewGame()
{
	std::vector<std::string> songList;
	songList.push_back("../data/music/Sixty_BPM.wav");
	std::shared_ptr<Song> song = std::make_shared<Song>(songList);

	//REINSTANTIATES RESPECTIVE MINIGAMES WHEN SWITCHING B/W THEM
	//Body of loop not needed for second minigame
	if(currentGame != 2)
	{
		logic = std::make_shared<MinigameLogic>(song);
		view = std::make_shared<MinigameView>(logic, app);
	}
	// Game Switching Part
	if(currentGame == 1)
	{
		//INSTANTIATE SOUS CHEF GAME
		logic_1 = std::make_shared<MinigameLogic_1>(song);
		view_1 = std::make_shared<MinigameView_1>(logic_1, app);
	}
	else if(currentGame == 2)
	{
		//INSTANTIATE PIZZA GAME
		logic_2 = std::make_shared<MinigameLogic_2>(song, 10); //pass maximum cuts allowed
		logic_2->setPosition(sf::Vector2f(app->getSize().x/2.f, app->getSize().y/2.f));
		view_2 = std::make_shared<MinigameView_2>(logic_2, app);
	}
	else if(currentGame == 3)
	{
		//INSTANTIATE CUTTING GAME
		logic_3 = std::make_shared<MinigameLogic_3>(song);
		view_3 = std::make_shared<MinigameView_3>(logic_3, app);
	}
	else if(currentGame == 4)
	{
		//INSTANTIATE DDR GAME
		logic_4 = std::make_shared<MinigameLogic_4>(song);
		view_4 = std::make_shared<MinigameView_4>(logic_4, app);
	}
}

// General game loop stays
/**
* Event checking for Minigame switching and playing
**/
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
			case sf::Keyboard::Num1:
				currentGame = 1;
				switchToNewGame();
				break;
			case sf::Keyboard::Num2:
				currentGame = 2;
				switchToNewGame();
				break;
			case sf::Keyboard::Num3:
				currentGame = 3;
				switchToNewGame();
				break;
			case sf::Keyboard::Num4:
				currentGame = 4;
				switchToNewGame();
				break;
			case sf::Keyboard::Space:
				// TODO: Call tapCheck on individual minigame logic
				switch(currentGame)
				{
					case 1:
						logic->tapCheck();
					break;
					case 2:
						logic_2->pushNewCut(); //no hit accuracy checking, scoring at end of game
					break;
					case 3:
						logic->tapCheck();
						view_3->splitBox(deltaTime);
					break;
					case 4:
						//INCLUDE INPUT LOGIC FOR DDR-MINIGAME
					break;
					default:
					break;
				}
				//logic->tapCheck();
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
	//State/Minigame switching
	switch(currentGame)
	{
		case 1:
			//INSERT GAME LOOP FOR MINIGAME_1
			view->update(deltaTime);
		    view_1->update(deltaTime);
		    view->draw();
			break;
		case 2:
			//INSERT GAME LOOP FOR MINIGAME_2
			logic_2->update(deltaTime);
			view_2->update(deltaTime);
			break;
		case 3:
			//INSERT GAME LOOP FOR MINIGAME_3
			view->update(deltaTime);
		  view_3->update(deltaTime);
		  view->draw();
			break;
		case 4:
			//INSERT GAME LOOP FOR MINIGAME_4
			//DDR-themed game
			view->update(deltaTime);
		  view_4->update(deltaTime);
		  view->draw();
			break;
		case 0:
		default:
			//GAME LOOP FOR MAIN MENU PERHAPS?
			break;
	}

}
