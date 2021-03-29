#include "Game.h"

Game::Game(std::string filename):
song(filename)
{
    tapNum = 0;
    backgroundColor = 0;
    isHit = false;
    actRegion = 0.3;
    winRegion = 0.15;
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
float Game::determinePrevTap(float songTime)
{
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

/*
Check whether the player did not tap in previous action region
*/
bool Game::hitCheck()
{
  if(isHit) {
    return true;
  }
  float curSongTime = song.getSongTime();
  float prevTap = determinePrevTap(curSongTime);
  std::cout << "curSongTime: " << curSongTime << std::endl;
  std::cout << "prevTap: " << prevTap << std::endl;
  //if song time is past tap region and no hits happened
  if(curSongTime - prevTap > actRegion)
  {
    backgroundColor = 0;
    std::cout << "No tap in action region" << std::endl;
    return false;
  }
}

void Game::tapCheck(sf::RenderWindow &app)
{
  // TODO: move this into the event manager
  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
  // {
      float curSongTime = song.getSongTime();
      float nextTap = determineNextTap(curSongTime);
      float prevTap = determinePrevTap(curSongTime);
      std::cout << "current to nextTap: " << std::abs(curSongTime - nextTap) << std::endl;
      std::cout << "current to prevTap: " << std::abs(curSongTime - prevTap) << std::endl;

      //current song time not in any tap action regions
      if((std::abs(curSongTime - nextTap) > actRegion && std::abs(curSongTime - prevTap) > actRegion))
      {
          backgroundColor = 0;

      }
      //current song time hit in success range
      else if (std::abs(curSongTime - nextTap) < winRegion || std::abs(curSongTime - prevTap) < winRegion)
      {
          backgroundColor = 1;
          std::cout << "Hit!" << std::endl;
          isHit = true;
      }
      //current song time hit in fail range
      else
      {
          backgroundColor = 2;
          std::cout << "Miss!" << std::endl;
          isHit = true;
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
