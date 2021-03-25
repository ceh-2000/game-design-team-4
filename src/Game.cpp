#include "Game.h"

Game::Game(std::string filename): 
song(filename)
{
    tapNum = 0;
    backgroundColor = 0;
}

Game::~Game() {}

void Game::setCurrentSong(std::string filename)
{
    // Set the current song to play
    // song(filename);
    // TODO: Issues setting this; possible fix is to make private variable song a pointer.
    song.play();
}

/*
Gets the previous hit given a song time
*/
float Game::determinePrevTap(float songTime){
    if(tapNum == 0){
        return song.getACorrectTiming(tapNum);
    }
    return song.getACorrectTiming(tapNum-1);  
}

/*
Gets the next hit given a song time
*/
float Game::determineNextTap(float songTime)
{
    float nextTap = song.getACorrectTiming(tapNum);
    if(std::abs(nextTap - 50000) < 0.01){
        return nextTap;
    }
    while (songTime > nextTap)
    {
        tapNum = tapNum + 1;
        nextTap = song.getACorrectTiming(tapNum);
    }

    return nextTap;
}

void Game::tapCheck(sf::RenderWindow &app){
    // TODO: move this into the event manager
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    // {
        float curSongTime = song.getSongTime();
        float nextTap = determineNextTap(curSongTime);
        float prevTap = determinePrevTap(curSongTime);
        std::cout << std::abs(curSongTime - nextTap) << std::endl;
        std::cout << std::abs(curSongTime - prevTap) << std::endl;
        if(std::abs(nextTap - 50000) < 0.001){
            backgroundColor = 0;
        }
        else if (std::abs(curSongTime - nextTap) < 0.5 || std::abs(curSongTime - prevTap) < 0.5)
        {
            backgroundColor = 1;
            std::cout << "Hit!" << std::endl;
        }
        else
        {
            backgroundColor = 2;
            std::cout << "Miss!" << std::endl;
        }
    //}
}

void Game::update(sf::RenderWindow &app, float deltaTime)
{
    // Clear screen and fill with blue
    if(backgroundColor == 0){
        app.clear(sf::Color::Blue);
    }
    else if(backgroundColor == 1){
        app.clear(sf::Color::Green);
    }
    else if(backgroundColor == 2){
        app.clear(sf::Color::Red);
    }

    // tapCheck(app);

    // Display
    app.display();
}
