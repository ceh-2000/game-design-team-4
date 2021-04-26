#include "Game.h"

Game::Game()
{
	std::vector<std::string> songList;
	std::vector<std::string> soundList;

	// TODO: Push more than one song and allow for rotating between songs
	songList.push_back("../data/music/Sixty_BPM.wav");
	soundList.push_back("../data/music/single_beat.wav"); //Sound to use in pizza game

	std::shared_ptr<Song> song = std::make_shared<Song>(songList, soundList);
	//std::shared_ptr<Song> sound = std::make_shared<Song>(soundList);

	logic = std::make_shared<MinigameLogic>(song);
  view = std::make_shared<MinigameView>(logic, app);

	logic_1 = std::make_shared<MinigameLogic_1>(song, app->getSize().x, app->getSize().y);
	logic_2 = std::make_shared<MinigameLogic_2>(song, 5); // Pass maximum cuts allowed
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
	std::vector<std::string> soundList;
	soundList.push_back("../data/music/single_beat.wav"); //Sound to use in pizza game
	songList.push_back("../data/music/Sixty_BPM.wav");
	logic->stopGame();
	std::shared_ptr<Song> song = std::make_shared<Song>(songList, soundList);

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
		logic_1 = std::make_shared<MinigameLogic_1>(song, app->getSize().x, app->getSize().y);
		view_1 = std::make_shared<MinigameView_1>(logic_1, app);
	}
	else if(currentGame == 2)
	{
		//INSTANTIATE PIZZA GAME
		logic_2 = std::make_shared<MinigameLogic_2>(song, 5); //pass maximum cuts allowed
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
	std::vector<std::string> songList;
	songList.push_back("../data/music/Sixty_BPM.wav");
	std::vector<std::string> soundList;
	soundList.push_back("../data/music/single_beat.wav"); //Sound to use in pizza game
	std::shared_ptr<Song> song = std::make_shared<Song>(songList, soundList);
	// Process events
	sf::Event event;
	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
	{
		this->isActive = false;
	}
	while (app->pollEvent(event))
	{
		//BROAD EVENTS
		switch (event.type)
		{
		case sf::Event::Closed:
			this->isActive = false;
			break; // Exit
		case sf::Event::KeyPressed:
			switch(event.key.code)
			{
				case sf::Keyboard::Q:
					this->isActive = false;
					break; // Exit
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
			}
			break;
		}

		//MINIGAME SPECIFIC OPERATIONS
		switch(currentGame)
		{
			case 1:
				minigame1EventHandler(deltaTime, event);
				break;
			case 2:
				minigame2EventHandler(deltaTime, event, song);
			  break;
			case 3:
				minigame3EventHandler(deltaTime, event);
			  break;
			case 4:
				minigame4EventHandler(deltaTime, event);
			  break;
		}
	}
}

void Game::minigame1EventHandler(const float &deltaTime, sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
			case sf::Keyboard::Left:
				logic_1->reactTap(logic->tapCheck(), false);
				break;
			case sf::Keyboard::Right:
				logic_1->reactTap(logic->tapCheck(), true);
				break;
			default:
			  break;
		}
	default:
		break;
	}
}

void Game::minigame2EventHandler(const float &deltaTime, sf::Event event, std::shared_ptr<Song> song)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
			case sf::Keyboard::Enter:
				if(song->getSoundStatus() != sf::Sound::Status::Playing)
					logic_2->playBeat();
				break;
			case sf::Keyboard::Space:
				logic_2->pushNewCut(); //no hit accuracy checking, scoring at end of game
				view_2->cutPizza();
				break;
		}
	default:
		break;
	}
}

void Game::minigame3EventHandler(const float &deltaTime, sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
			case sf::Keyboard::Space:
				logic->tapCheck();
				view_3->splitBox(deltaTime);
				break;
		}
		break;
	}
}

void Game::minigame4EventHandler(const float &deltaTime, sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
			case sf::Keyboard::Left:
				view_4->reachInput(0);
				break;
			case sf::Keyboard::Right:
				view_4->reachInput(3);
				break;
			case sf::Keyboard::Up:
				view_4->reachInput(2);
				break;
			case sf::Keyboard::Down:
				view_4->reachInput(1);
				break;
			default:
				break;
		}
	default:
		break;
	}
}

void Game::update(const float &deltaTime)
{
    // TODO: move this call into the individual view updates
    app->clear();
	checkEvent(deltaTime);

 	// TODO: make a round subloop for the minigame loops
	//State/Minigame switching
	switch(currentGame)
	{
		case 1:
			//INSERT GAME LOOP FOR MINIGAME_1
			logic_1->update(deltaTime, logic->regionCheck());
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
