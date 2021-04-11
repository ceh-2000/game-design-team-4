#pragma once
#include <SFML/Graphics.hpp>
#include <math.h> 
#include <iostream>

class BeatBoxLogic
{
public:
    // Constructor
    BeatBoxLogic(sf::Vector2f startPos, sf::Vector2f endPos, sf::Vector2f velocity, float songTimeHit);

    // Getters, setters, and short methods
    sf::Vector2f getStartPos(){ return startPos; }
    sf::Vector2f getEndPos(){ return endPos; }
    sf::Vector2f getCurPos(){ return curPos;  }
    sf::Vector2f getVelocity(){ return velocity;  }
    float getSongTime(){ return songTimeHit; }

    void setCurPos(sf::Vector2f cPos){ curPos = cPos; }
    void setVelocity(sf::Vector2f vel); // Implement in cpp file

    bool isAtStart(){ if(std::abs(curPos.x - startPos.x) < 0.01){return true; } return false; }
    bool isAtEnd(){ if(std::abs(curPos.x - endPos.x) < 0.01){return true; } return false; }

    // Methods with logic
    void move(float deltaTime);
    void moveX(float deltaTime);
    void moveY(float deltaTime);
    bool update(float deltaTime, float curSongTime);

private:
    sf::Vector2f startPos;
    sf::Vector2f endPos;
    sf::Vector2f curPos;
    sf::Vector2f velocity;
    float songTimeHit;
};