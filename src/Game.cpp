#include "Game.h"

Game::Game(std::string filename):
song(filename)
{
    tapNum = 0;
    backgroundColor = 0;
    isHit = false;
    actRegion = 0.45;
    winRegion = 0.15;
    almostRegion = 0.3;
    int counter = 0;

    duration = .075;
    elapsedDuration = duration;


    // load sprite sheet for Satsana
    if(!texture.loadFromFile("../data/art/SatsanaSheet.png")){
        std::cout << "Could not load Satsana sprite sheet." << std::endl;
    }
    rectSourceSprite.left = 0;
    rectSourceSprite.top = 0;
    rectSourceSprite.width = 128;
    rectSourceSprite.height = 128;

    sprite.setTexture(texture);
    sprite.setPosition(0, 0);  
    sprite.setTextureRect(rectSourceSprite);

    //load in the font for result text
    if(!font.loadFromFile("../data/fonts/orange_kid.ttf")){
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }
    resultText.setFont(font);
    resultText.setString("");
    resultText.setCharacterSize(24);
    resultText.setFillColor(sf::Color::Black);
    resultText.setPosition(130, 40);
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
void Game::regionCheck()
{   
    float curSongTime = song.getSongTime();
    float nextTap = determineNextTap(curSongTime);
    float prevTap = determinePrevTap(curSongTime);

    // Kick-off an animation to show that the user missed because they never hit
    if(isHit == false && (std::abs(curSongTime - nextTap) > actRegion && std::abs(curSongTime - prevTap) > actRegion)){
        std::cout << "No tap in action region" << std::endl;
        std::cout << "Miss!" << std::endl;
        backgroundColor = 3;
        isHit = true;
        animate = true;
        resultText.setString("Try Again!");
    }

    // Reset once we reenter an active region
    else if(std::abs(curSongTime - nextTap) < actRegion){
        isHit = false;
    }
}

void Game::tapCheck(sf::RenderWindow &app)
{
      float curSongTime = song.getSongTime();
      float nextTap = determineNextTap(curSongTime);
      float prevTap = determinePrevTap(curSongTime);

      std::cout << "current to nextTap: " << std::abs(curSongTime - nextTap) << std::endl;
      std::cout << "current to prevTap: " << std::abs(curSongTime - prevTap) << std::endl;

      //current song time not in any tap action regions
      if((std::abs(curSongTime - nextTap) > actRegion && std::abs(curSongTime - prevTap) > actRegion))
      {
          isHit = false;
          backgroundColor = 0;
      }

      //current song time hit in success range
      else if (std::abs(curSongTime - nextTap) < winRegion || std::abs(curSongTime - prevTap) < winRegion)
      {
          std::cout << "Hit!" << std::endl;
          backgroundColor = 1;
          isHit = true;
          animate = true;
          resultText.setString("Perfect!");
      }
      //current song time hit in almost range
      else if (std::abs(curSongTime - nextTap) > winRegion && std::abs(curSongTime - prevTap) < almostRegion
              || std::abs(curSongTime - nextTap) < winRegion && std::abs(curSongTime - prevTap) > almostRegion)
      {
          std::cout << "Almost!" << std::endl;
          backgroundColor = 2;
          isHit = true;
          animate = true;
          resultText.setString("Almost!");
      }
      //current song time hit in fail range
      else
      {
          std::cout << "Miss!" << std::endl;
          backgroundColor = 3;
          isHit = true;
          animate = true;
          resultText.setString("Try Again!");
      }
}

void Game::update(sf::RenderWindow &app, float deltaTime)
{

    regionCheck();

    // TODO: Extract all view logic to a view class

    // Animation logic
    if(animate){
        elapsedDuration += deltaTime;

        while(elapsedDuration > duration){
            elapsedDuration -= duration;

            // cycle through 6 frames of talking
            if(rectSourceSprite.left == 256){
                rectSourceSprite.left = 0;
            }
            else{
                rectSourceSprite.left += 128;
            }
            counter++;
            if(counter == 6){
                animate = false;
                backgroundColor = 0;
                counter = 0;
                resultText.setString("");
            }
        }
        sprite.setTextureRect(rectSourceSprite);
    }

    // Draw background and animation
    if(backgroundColor == 0){
        app.clear(sf::Color::Blue);
    }
    else if(backgroundColor == 1){
        app.clear(sf::Color::Green);
    }
    else if(backgroundColor == 2){
        app.clear(sf::Color::Yellow);
    }
    else if(backgroundColor == 3){
        app.clear(sf::Color::Red);
    }

    app.draw(resultText);
    app.draw(sprite);

    //Upcoming changes?
    //if(animate)
    //    Animation(deltaTime, 3, 0.75f, false, resultText, sprite, rectSourceSprite, app);

    app.draw(resultText);
    app.draw(sprite);


    // Display
    app.display();
}
