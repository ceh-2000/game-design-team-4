#pragma once
#ifndef MINIGAME_LOGIC_2
#define MINIGAME_LOGIC_2

#include "MinigameLogic.h"

class MinigameLogic_2 {
private:
    std::shared_ptr<Song> song; //Song is background run

    //Pizza physical attributes
    float pizzaRadius = 200.0f;
    std::vector<float> cutAngles; //Angles of pizza player cut (Also denotes cut lines)
    int maxCuts;
    sf::Vector2f position;
    float pizzaAngle; //Current pizza rotation angle (in radians)

    //Pizza logic Attributes
    float angleSpeed;
    float goalAngle; // Target angle for pizza slices; Computed in radians
    float rotTime = 0.0f; //Current time in rotation

    //Minigame logic attributes
    float gameScore;
    float revTime = 10.0f; //total time call beats played

    sf::Vector2f knifePos;
    float knifeSpeed = 2500;

public:
    MinigameLogic_2(std::shared_ptr<Song> song, int maxCuts);

    void move(const float &dt);

    int getScore() { return gameScore; }

    float getPRadius() const { return pizzaRadius; }

    void setPRadius(float p) { pizzaRadius = p; }

    void setPosition(sf::Vector2f v) { position = v; }

    sf::Vector2f getPosition() { return position; }

    int getMaxCuts() const { return maxCuts; }

    float getPAngle() const { return pizzaAngle; }

    void setPAngle(float theta) { pizzaAngle = theta; }

    void rotatePizza(float theta) { pizzaAngle += theta; }

    float getAngleSpeed() { return angleSpeed; }

    void setAngleSpeed(float s) { angleSpeed = s; }

    std::vector<float> getCutAngles() const { return cutAngles; }

    void pushBackCutAngle(float angle) { cutAngles.push_back(angle); }

    float calcScore(); //Calculate score
    float getRotTime() { return rotTime; }

    void checkEvent(sf::RenderWindow &app);

    void update(float deltaTime);

    void pushNewCut();

    sf::Vector2f getKnifePos() { return knifePos; }

    float getKnifeSpeed() { return knifeSpeed; }

    void setKnifePos(sf::Vector2f pos) { knifePos = pos; }

    sf::Time playBeat();

    //Use the state enum to track the state of the game
    enum gameState { PLAYING = 0, ENDING = 1, STOPPED = 2, PAUSED = 3 };
    gameState state = PLAYING;

};

#endif
