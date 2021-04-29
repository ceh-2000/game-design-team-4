#include "Game.h"

Game::Game() {
    std::vector<std::string> songList;

    // TODO: Push more than one song and allow for rotating between songs
    songList.push_back("../data/music/Sixty_BPM.wav");

    std::shared_ptr<Song> song = std::make_shared<Song>(songList);
    this->cut_scene = std::make_shared<CutScene>(app);
    this->main_menu = std::make_shared<MainMenu>(app);

    this->logic = std::make_shared<MinigameLogic>(song);
    this->view = std::make_shared<MinigameView>(logic, app);
//
//    this->logic_1 = std::make_shared<MinigameLogic_1>(song, app->getSize().x, app->getSize().y);
//    this->logic_2 = std::make_shared<MinigameLogic_2>(song, 10); // Pass maximum cuts allowed
//
//    // TODO: Position setting should be refactored
//    this->logic_2->setPosition(sf::Vector2f(app->getSize().x / 2.0f, app->getSize().y / 2.f));
//    this->logic_2->setKnifePos(
//            sf::Vector2f(logic_2->getPosition().x + 1.5f * logic_2->getPRadius(), logic_2->getPosition().y));
//    this->logic_3 = std::make_shared<MinigameLogic_3>(song);
//    this->logic_4 = std::make_shared<MinigameLogic_4>(song);
//
//    this->view_1 = std::make_shared<MinigameView_1>(logic_1, app);
//    this->view_2 = std::make_shared<MinigameView_2>(logic_2, app);
//    this->view_3 = std::make_shared<MinigameView_3>(logic_3, app);
//    this->view_4 = std::make_shared<MinigameView_4>(logic_4, app);
}

void Game::switchToNewGame() {
    this->elapsedTime = 0;

    std::vector<std::string> songList;
    songList.push_back("../data/music/Sixty_BPM.wav");
    this->logic->stopGame();
    std::shared_ptr<Song> song = std::make_shared<Song>(songList);

    //REINSTANTIATES RESPECTIVE MINIGAMES WHEN SWITCHING B/W THEM
    //Body of loop not needed for second minigame
    if (this->currentGame != 2 && this->currentGame != 5) {
        this->logic = std::make_shared<MinigameLogic>(song);
        this->view = std::make_shared<MinigameView>(this->logic, this->app);
        this->logic->startGame();
    }
    // Game Switching Part
    if (currentGame == 1) {
        //INSTANTIATE SOUS CHEF GAME
        this->logic_1 = std::make_shared<MinigameLogic_1>(song, this->app->getSize().x, this->app->getSize().y);
        this->view_1 = std::make_shared<MinigameView_1>(this->logic_1, this->app);
    } else if (currentGame == 2) {
        //INSTANTIATE PIZZA GAME
        this->logic_2 = std::make_shared<MinigameLogic_2>(song, 10); //pass maximum cuts allowed
        this->logic_2->setPosition(sf::Vector2f(this->app->getSize().x / 2.f, this->app->getSize().y / 2.f));
        this->logic_2->setKnifePos(
                sf::Vector2f(this->logic_2->getPosition().x + 1.5 * this->logic_2->getPRadius(), this->logic_2->getPosition().y));
        this->view_2 = std::make_shared<MinigameView_2>(this->logic_2, app);
    } else if (this->currentGame == 3) {
        //INSTANTIATE CUTTING GAME
        this->logic_3 = std::make_shared<MinigameLogic_3>(song);
        this->view_3 = std::make_shared<MinigameView_3>(this->logic_3, this->app);
    } else if (currentGame == 4) {
        //INSTANTIATE DDR GAME
        this->logic_4 = std::make_shared<MinigameLogic_4>(song);
        this->view_4 = std::make_shared<MinigameView_4>(this->logic_4, this->app);
    } else if (this->currentGame == 5) {
        this->cut_scene->setScore(this->score);
    }
}

/**
* Event checking for Minigame switching and playing
**/
void Game::checkEvent(const float &deltaTime) {
    // Process events
    sf::Event event;
    while (this->app->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                this->isActive = false;
                break; // Exit
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Q:
                        this->isActive = false;
                        break; // Exit
                    case sf::Keyboard::Num1:
                        this->currentGame = 1;
                        switchToNewGame();
                        break;
                    case sf::Keyboard::Num2:
                        this->currentGame = 2;
                        switchToNewGame();
                        break;
                    case sf::Keyboard::Num3:
                        this->currentGame = 3;
                        switchToNewGame();
                        break;
                    case sf::Keyboard::Num4:
                        this->currentGame = 4;
                        switchToNewGame();
                        break;
                    case sf::Keyboard::Space:
                        switch (this->currentGame) {
                            case 2:
                                this->logic_2->pushNewCut(); //no hit accuracy checking, scoring at end of game
                                this->view_2->cutPizza(deltaTime);
                                break;
                            case 3:
                                this->logic->tapCheck();
                                this->view_3->splitBox(deltaTime);
                                this->logic_3->updateScore(logic->tapCheck(), logic->regionCheck());
                                break;
                            case 5:
                                this->endRound();
                                break;
                            case 6:
                                this->currentGame = 1;
                                this->switchToNewGame();
                                this->logic->startGame();
                            default:
                                break;
                        }
                        break;
                    case sf::Keyboard::Left:
                        switch (this->currentGame) {
                            case 1:
                                this->logic_1->reactTap(this->logic->tapCheck(), false);
                                break;
                            case 4:
                                this->view_4->reachInput(0, this->logic->tapCheck());
                            default:
                                break;
                        }
                        break;
                    case sf::Keyboard::Right:
                        switch (this->currentGame) {
                            case 1:
                                this->logic_1->reactTap(this->logic->tapCheck(), true);
                                break;
                            case 4:
                                this->view_4->reachInput(3, this->logic->tapCheck());
                                break;
                            default:
                                break;
                        }
                        break;
                    case sf::Keyboard::Up:
                        switch (this->currentGame) {
                            case 4:
                                this->view_4->reachInput(2, this->logic->tapCheck());
                                break;
                        }
                        break;

                    case sf::Keyboard::Down:
                        switch (this->currentGame) {
                            case 4:
                                this->view_4->reachInput(1, this->logic->tapCheck());
                                break;
                        }
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}

void Game::endRound() {
    // Reset minigame variables
    this->score = 0;
    this->elapsedTime = 0.0f;

    // Show the first minigame again
    if (this->round < this->numOfRounds) {
        this->currentGame = 1;
        this->switchToNewGame();
        this->round++;
    }
    // Show the main menu
    else{
        this->currentGame = 6;
        this->round = 0;
    }
}

void Game::update(const float &deltaTime) {
    // TODO: move this call into the individual view updates
    this->app->clear();
    checkEvent(deltaTime);

    // Check if we have played the song for long enough
    if (this->elapsedTime > this->minigameTime and currentGame != 6) {
        // Reset time variable that checks time for minigame 2; 1, 3, & 4 rely on song time
        this->elapsedTime = 0.0f;

        // Get the score from the game that just finished
        switch (this->currentGame) {
            case 1:
                this->score += this->logic_1->getScore();
                break;
            case 2:
                this->score += this->logic_2->getScore();
                break;
            case 3:
                this->score += this->logic_3->getScore();
                break;
            case 4:
                this->score += this->logic_4->getScore();
                break;
            default:
                break;
        }

        if (this->currentGame < 5) {
            this->currentGame++;
            this->switchToNewGame();
        } else {
            this->endRound();
        }
    }


    switch (this->currentGame) {
        case 1:
            // Sous chef game
            this->logic_1->update(deltaTime, this->logic->regionCheck());
            this->view_1->update(deltaTime);
            this->view->draw();
            break;
        case 2:
            // Pizza cutting game
            this->logic_2->update(deltaTime);
            this->view_2->update(deltaTime);
            break;
        case 3:
            // Chopping game
            this->view->update(deltaTime);
            this->view_3->update(deltaTime);
            this->view->draw();
            break;
        case 4:
            // DDR-themed game
            this->view->update(deltaTime);
            this->view_4->update(deltaTime);
            this->view->draw();
            break;
        case 5:
            // Cut scene
            this->cut_scene->draw(deltaTime);
            break;
        case 6:
            // Main menu
            this->main_menu->draw(deltaTime);
            break;
        default:
            break;
    }

    this->elapsedTime = this->elapsedTime + deltaTime;
}
