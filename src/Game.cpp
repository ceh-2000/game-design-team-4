#include "Game.h"

Game::Game(float tTime, std::string filename): 
tapTime(tTime),
song(filename)
{
}

Game::~Game(){}

void Game::setCurrentSong(std::string filename){
    // Set the current song to play
    // song(filename); 
    // TODO: Issues setting this; possible fix is to make private variable song a pointer.
    song.play();
}

void Game::update(sf::RenderWindow& app, float deltaTime){
    // Clear screen and fill with blue
    app.clear(sf::Color::Blue);
    
    float curSongTime = song.getSongTime();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(std::abs(curSongTime - tapTime) < 0.5){
            std::cout << curSongTime << std::endl;
            app.clear(sf::Color::Green);
        }
        else{
            app.clear(sf::Color::Red);
        }
    }

    // Display
    app.display();
}

