#include "Game.h"

Game::Game(std::shared_ptr<Song> song) {

    //prevent repeat events when holding down
    app->setKeyRepeatEnabled(false);

    this->song = song;
    this->song->setGameStateAudio(this->currentGame, this->round);
    cut_scene = std::make_shared<Cutscene>(app);
    main_menu = std::make_shared<MainMenu>(app);
    logic = std::make_shared<MinigameLogic>(this->song, sf::Vector2f(0.15, 0.15));
    view = std::make_shared<MinigameView>(logic, app);
}

void Game::switchToNewGame() {
    elapsedTime = 0;
    logic->stopGame();
    song->setGameStateAudio(this->currentGame, this->round);
    //REINSTANTIATES RESPECTIVE MINIGAMES WHEN SWITCHING B/W THEM
    // Game Switching Part
    switch (currentGame) {
        case 1:
            //INSTANTIATE SOUS CHEF GAME
            logic = std::make_shared<MinigameLogic>(song, sf::Vector2f(0.15, 0.15));
            view = std::make_shared<MinigameView>(logic, app);
            logic->startGame();
            logic_1 = std::make_shared<MinigameLogic_1>(song, app->getSize().x, app->getSize().y);
            view_1 = std::make_shared<MinigameView_1>(logic_1, app);
            minigameTime = 30.0f;
            break;
        case 2:
            //INSTANTIATE PIZZA GAME
            logic_2 = std::make_shared<MinigameLogic_2>(song, round); //pass maximum cuts allowed
            view_2 = std::make_shared<MinigameView_2>(logic_2, app);
            minigameTime = 100.0f;
            break;
        case 3:
            //INSTANTIATE CUTTING GAME
            logic = std::make_shared<MinigameLogic>(song, sf::Vector2f(0.15, 0.15));
            view = std::make_shared<MinigameView>(logic, app);
            logic->startGame();
            logic_3 = std::make_shared<MinigameLogic_3>(song, round);
            view_3 = std::make_shared<MinigameView_3>(logic_3, app);
            minigameTime = 30.0f;
            break;
        case 4:
            //INSTANTIATE DDR GAME
            logic = std::make_shared<MinigameLogic>(song, sf::Vector2f(0.15, 0.15));
            view = std::make_shared<MinigameView>(logic, app);
            logic->startGame();
            logic_4 = std::make_shared<MinigameLogic_4>(song);
            view_4 = std::make_shared<MinigameView_4>(logic_4, app);
            minigameTime = 30.0f;
            break;
        case 5:
            cut_scene->setFinalChefName(main_menu->getFinalChef());
            cut_scene->setName(main_menu->getUserChefName());
            cut_scene->setScore(score);
            cut_scene->setRank(roundRank[round]);
            break;
        case 6:
            round = 0;
            break;
        default:
            break;
    }
}

/**
* Event checking for Minigame switching and playing
**/

void Game::checkEvent(const float &deltaTime) {
    // Process events
    sf::Event event;
    while (app->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                isActive = false;
                break; // Exit
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Q:
                        isActive = false;
                        break; // Exit
                    case sf::Keyboard::Escape:
                        switch (currentGame) {
                            case 6:
                                main_menu->setCurrentScreen(0);
                                break;
                            default:
                                break;
                        }
                        break;
                    case sf::Keyboard::Space:
                        if (currentGame == 5) {
                            endRound();
                        }
                        break;
                    default:
                        break;
                }
            default:
                break;
        }

        switch (currentGame) {
            case 1:
                minigame1EventHandler(deltaTime, event);
                break;
            case 2:
                minigame2EventHandler(deltaTime, event);
                break;
            case 3:
                minigame3EventHandler(deltaTime, event);
                break;
            case 4:
                minigame4EventHandler(deltaTime, event);
                break;
            case 6:
                mainMenuEventHandler(deltaTime, event);
                break;
            default:
                break;
        }
    }
}

void Game::calcRoundRank() {
    // Calculate minigame rank tally
    int tally = 0;
    for (std::string grade : scoreRank[round]) {
        if (grade == "S")
            tally += 5;
        else if (grade == "A")
            tally += 4;
        else if (grade == "B")
            tally += 3;
        else if (grade == "C")
            tally += 2;
        else if (grade == "D")
            tally += 1;
    }

    // Convert tally to round rank
    if (tally >= 19)
        roundRank[round] = "S";
    else if (tally >= 15)
        roundRank[round] = "A";
    else if (tally >= 11)
        roundRank[round] = "B";
    else if (tally >= 7)
        roundRank[round] = "C";
    else if (tally >= 3)
        roundRank[round] = "D";
    else {
        roundRank[round] = "F";
    }
}

void Game::minigame1EventHandler(const float &deltaTime, sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Left:
                    logic_1->reactTap(logic->tapCheck(), false);
                    view_1->animatePostHit(logic->tapCheck(), round, deltaTime);
                    break;
                case sf::Keyboard::Right:
                    logic_1->reactTap(logic->tapCheck(), true);
                    view_1->animatePostHit(logic->tapCheck(), round, deltaTime);
                    break;
                default:
                    break;
            }
            break;
    }
}

void Game::minigame2EventHandler(const float &deltaTime, sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Space:
                    switch (logic_2->state) {
                        case MinigameLogic_2::gameState::PLAYING:
                            logic_2->pushNewCut(); //no hit accuracy checking, scoring at end of game
                            view_2->cutPizza(deltaTime);
                            break;
                        case MinigameLogic_2::gameState::ENDING:
                            score += logic_2->getScore();
                            scoreRank.at(round).at(currentGame - 1) = logic_2->gradeMinigame();
                            currentGame++;
                            switchToNewGame();
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Keyboard::Return:
                    if (logic_2->getCutAngles().size() == 0) {
                        logic_2->playBeat(*app);
                    }
                    break;
                default:
                    break;
            }
            break;
    }
}

void Game::minigame3EventHandler(const float &deltaTime, sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Space:
                    logic->tapCheck();
                    logic_3->updateScore(logic->tapCheck());
                    view_3->splitBox(deltaTime);
                    view_3->animatePostHit(logic->tapCheck(), round, deltaTime);
                    break;
                default:
                    break;
            }
            break;
    }
}

void Game::minigame4EventHandler(const float &deltaTime, sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::Down:
                case sf::Keyboard::Up:
                case sf::Keyboard::Right:
                    view_4->reachInput(multiArrowInput(), logic->tapCheck());
                    view_4->animatePostHit(logic->tapCheck(), round, deltaTime);
                    break;
                case sf::Keyboard::Space:
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Game::mainMenuEventHandler(const float &deltaTime, sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Return:
                    switch (main_menu->chooseSelection()) {
                        case 0:
                            currentGame = 1;
                            switchToNewGame();
                            logic->startGame();
                            break;
                        case 1:
                        case 2:
                            main_menu->setCurrentScreen(main_menu->chooseSelection());
                            break;
                        default:
                            break;
                    }
                case sf::Keyboard::Up:
                    main_menu->moveUp();
                    break;
                case sf::Keyboard::Down:
                    main_menu->moveDown();
                    break;
                case sf::Keyboard::Right:
                    main_menu->selectRight();
                    break;
                case sf::Keyboard::Left:
                    main_menu->selectLeft();
                    break;
                default:
                    break;
            }
            break;

        case sf::Event::TextEntered:
            if (main_menu->getCurrentScreen() == 1 && main_menu->getOptionSelected() == 0) {
                if (event.text.unicode == sf::Keyboard::BackSpace || event.text.unicode == sf::Keyboard::Delete ||
                    event.text.unicode == 8) {
                    if (main_menu->getUserChefName().getSize() > 0) {
                        main_menu->setUserChefName(
                                main_menu->getUserChefName().substring(0,
                                                                       main_menu->getUserChefName().getSize() - 1));
                    }
                } else if ((event.text.unicode <= 122 && event.text.unicode >= 97) ||  (event.text.unicode <= 90 && event.text.unicode >= 65)) {
                    main_menu->addTextToName(event.text.unicode);
                }
            }
            break;
        default:
            break;
    }
}

int Game::multiArrowInput() {
    int inputScore = 0;

    left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    if (up && right) inputScore = 4;
    else if (down && right) inputScore = 5;
    else if (left && right) inputScore = 6;
    else if (down && left) inputScore = 7;
    else if (down && up) inputScore = 8;
    else if (left && up) inputScore = 9;
    else if (left) inputScore = 0;
    else if (down) inputScore = 1;
    else if (up) inputScore = 2;
    else if (right) inputScore = 3;

    return inputScore;
}

void Game::endRound() {
    // Reset minigame variables
    score = 0;
    elapsedTime = 0.0f;

    // Show the first minigame again
    if (round < numOfRounds - 1) {
        if (roundRank[round] != "F") {
            round++;
        }
        currentGame = 1;
        switchToNewGame();
    }
        // Show the main menu
    else {
        currentGame = 6;
        switchToNewGame();
    }
}

// TODO: Otherwise show the main menu
void Game::update(const float &deltaTime) {
    // TODO: move this call into the individual view updates
    app->clear();
    checkEvent(deltaTime);

    // Check if we have played the song for long enough
    if (elapsedTime > minigameTime and currentGame != 6) {
        // Reset time variable that checks time for minigame 2; 1, 3, & 4 rely on song time
        elapsedTime = 0.0f;

        // Get the score from the game that just finished
        switch (currentGame) {
            case 1:
                score += logic_1->getScore();
                scoreRank.at(round).at(currentGame - 1) = logic_1->gradeMinigame();
                break;
            case 3:
                score += logic_3->getScore();
                scoreRank.at(round).at(currentGame - 1) = logic_3->gradeMinigame();
                break;
            case 4:
                score += logic_4->getScore();
                scoreRank.at(round).at(currentGame - 1) = logic_4->gradeMinigame();
                break;
            default:
                break;
        }

        if (currentGame == 4) {
            calcRoundRank();
        }

        if (currentGame < 5 and currentGame != 2) {
            currentGame++;
            switchToNewGame();
        }
    }

    int cutsceneNum;
    switch (currentGame) {
        case 1:
            // Sous chef game
            logic_1->update(deltaTime, logic->regionCheck());
            view_1->update(deltaTime, this->round);
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
            view_3->update(deltaTime, this->round);
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
            cutsceneNum = 1;
            if (round == numOfRounds - 1 and roundRank[round] != "F") {
                cutsceneNum = 2;
            }
            cut_scene->selectCutscene(cutsceneNum);
            cut_scene->update(deltaTime, cutsceneNum);
            break;
        case 6:    // Main menu
            main_menu->draw(deltaTime, main_menu->getCurrentScreen());
            break;
        default:
            break;
    }
    elapsedTime = elapsedTime + deltaTime;
}