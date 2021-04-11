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
    void normalizeVelocity(); 

    bool isAtStart(){ if(std::abs(curPos.x - startPos.x) < 0.01){return true; } return false; }
    bool isAtEnd(){ if(std::abs(curPos.x - endPos.x) < 0.01){return true; } return false; }

    // Methods with logic
    void move(const float& deltaTime);
    void moveX(const float& deltaTime);
    void moveY(const float& deltaTime);
    bool update(const float& deltaTime, const float& curSongTime);

private:
    sf::Vector2f startPos;
    sf::Vector2f endPos;
    sf::Vector2f curPos;
    sf::Vector2f velocity;
    float songTimeHit;
};