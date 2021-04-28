#include "Game.h"

Game::Game()
{
	std::vector<std::string> songList;
	std::vector<std::string> soundList;

	// TODO: Push more than one song and allow for rotating between songs
	songList.push_back("../data/music/Sixty_BPM.wav");
	soundList.push_back("../data/music/single_beat.wav"); //Sound to use in pizza game

	std::shared_ptr<Song> song = std::make_shared<Song>(songList, soundList);
	cut_scene = std::make_shared<CutScene>(app);
	//std::shared_ptr<Song> sound = std::make_shared<Song>(soundList);

	logic = std::make_shared<MinigameLogic>(song);
  view = std::make_shared<MinigameView>(logic, app);

	logic_1 = std::make_shared<MinigameLogic_1>(song, app->getSize().x, app->getSize().y);
	logic_2 = std::make_shared<MinigameLogic_2>(song, 10); // Pass maximum cuts allowed
	logic_3 = std::make_shared<MinigameLogic_3>(song);
	logic_4 = std::make_shared<MinigameLogic_4>(song);

    view_1 = std::make_shared<MinigameView_1>(logic_1, app);
    view_2 = std::make_shared<MinigameView_2>(logic_2, app);
    view_3 = std::make_shared<MinigameView_3>(logic_3, app);
    view_4 = std::make_shared<MinigameView_4>(logic_4, app);
}

void Game::switchToNewGame() {
	this->elapsedTime = 0;

	std::vector<std::string> songList;
	std::vector<std::string> soundList;
	soundList.push_back("../data/music/single_beat.wav"); //Sound to use in pizza game
	songList.push_back("../data/music/Sixty_BPM.wav");
	logic->stopGame();
	std::shared_ptr<Song> song = std::make_shared<Song>(songList, soundList);

	//REINSTANTIATES RESPECTIVE MINIGAMES WHEN SWITCHING B/W THEM
	//Body of loop not needed for second minigame
	if(currentGame != 2 && currentGame != 5) {
		logic = std::make_shared<MinigameLogic>(song);
		view = std::make_shared<MinigameView>(logic, app);
	}
	// Game Switching Part
	if(currentGame == 1) {
		//INSTANTIATE SOUS CHEF GAME
		logic_1 = std::make_shared<MinigameLogic_1>(song, app->getSize().x, app->getSize().y);
		view_1 = std::make_shared<MinigameView_1>(logic_1, app);
	} else if(currentGame == 2) {
		//INSTANTIATE PIZZA GAME
		logic_2 = std::make_shared<MinigameLogic_2>(song, 10); //pass maximum cuts allowed
		view_2 = std::make_shared<MinigameView_2>(logic_2, app);
	} else if(currentGame == 3) {
		//INSTANTIATE CUTTING GAME
		logic_3 = std::make_shared<MinigameLogic_3>(song);
		view_3 = std::make_shared<MinigameView_3>(logic_3, app);
	} else if(currentGame == 4) {
		//INSTANTIATE DDR GAME
		logic_4 = std::make_shared<MinigameLogic_4>(song);
		view_4 = std::make_shared<MinigameView_4>(logic_4, app);
	} else if (currentGame == 5) {
			this->cut_scene->setScore(this->score);
	}
}

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
			case 5:
				if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
					this->endRound();
				}
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
					logic_2->playBeat(*app);
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
				logic_3->updateScore(logic->tapCheck(), logic->regionCheck());
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
				view_4->reachInput(0, logic->tapCheck());
				break;
			case sf::Keyboard::Right:
				view_4->reachInput(3, logic->tapCheck());
				break;
			case sf::Keyboard::Up:
				view_4->reachInput(2, logic->tapCheck());
				break;
			case sf::Keyboard::Down:
				view_4->reachInput(1, logic->tapCheck());
				break;
			default:
				break;
		}
	default:
		break;
	}
}

void Game::endRound() {
  if (round < numOfRounds) {
      this->elapsedTime = 0.0f;
      this->currentGame = 1;
      this->switchToNewGame();
      this->score = 0;
      this->round++;
    }
}
    // TODO: Otherwise show the main menu
void Game::update(const float &deltaTime) {
    // TODO: move this call into the individual view updates
    app->clear();
    checkEvent(deltaTime);

    // Check if we have played the song for long enough
    if (this->elapsedTime > this->minigameTime) {
        // Reset time variable that checks time for minigame 2; 1, 3, & 4 rely on song time
        this->elapsedTime = 0.0f;

        // Get the score from the game that just finished
        switch (this->currentGame) {
            case 1:
                this->score += logic_1->getScore();
                break;
            case 2:
                this->score += logic_2->getScore();
                break;
            case 3:
                this->score += logic_3->getScore();
                break;
            case 4:
                this->score += logic_4->getScore();
                break;
            default:
                break;
        }

        if (this->currentGame < 5) {
            this->currentGame++;
            this->switchToNewGame();
        } else {
            endRound();
        }
    }


    switch (this->currentGame) {
        case 1:
            // Sous chef game
            logic_1->update(deltaTime, logic->regionCheck());
            view_1->update(deltaTime);
            view->draw();
            break;
        case 2:
            // Pizza cutting game
            logic_2->update(deltaTime);
            view_2->update(deltaTime);
            break;
        case 3:
            // Chopping game
            view->update(deltaTime);
            view_3->update(deltaTime);
            view->draw();
            break;
        case 4:
            // DDR-themed game
            view->update(deltaTime);
            view_4->update(deltaTime);
            view->draw();
            break;
        case 5:
            // Cut scene
            this->cut_scene->draw(deltaTime);
        default:
            //GAME LOOP FOR MAIN MENU PERHAPS?
            break;
    }

    this->elapsedTime = elapsedTime + deltaTime;
}
