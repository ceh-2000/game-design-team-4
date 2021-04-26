#pragma once
#ifndef MINIGAME_LOGIC_2
#define MINIGAME_LOGIC_2
#include "MinigameLogic.h"
class MinigameLogic_2
{
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
    float knifeSpeed = 5000;
    bool soundPlaying = false;

public:
    MinigameLogic_2(std::shared_ptr<Song> song, int maxCuts);
    void move(const float& dt);

    //GETTERS AND SETTERS
    float getPRadius() const { return pizzaRadius; }
    void setPRadius(float p) { pizzaRadius = p; }

    sf::Vector2f getPosition() { return position; }
    void setPosition(sf::Vector2f v) { position = v; }

    int getMaxCuts() const { return maxCuts; }
    void setMaxCuts(int c) { maxCuts = c; }

    bool isSoundPlaying() { return soundPlaying; }

    float getPAngle() const { return pizzaAngle; }
    void setPAngle(float theta) { pizzaAngle = theta; }
    void rotatePizza(float theta) { pizzaAngle += theta; }

    float getAngleSpeed() { return angleSpeed; }
    void setAngleSpeed(float s) { angleSpeed = s; }

    sf::Vector2f getKnifePos() { return knifePos; }
    void setKnifePos(sf::Vector2f pos) { knifePos = pos; }

    float getKnifeSpeed() { return knifeSpeed; }
    void setKnifeSpeed(float ks) { knifeSpeed = ks; }

    std::vector<float> getCutAngles() const { return cutAngles; }
    void pushBackCutAngle(float angle) { cutAngles.push_back(angle); }
    float getRotTime() { return rotTime; }

    //GAME OPERATIONS
    void checkEvent(sf::RenderWindow &app);
    void update(float deltaTime);
    float calcScore(); //Calculate score

    void pushNewCut();
    //Song method that retrieves time
    void playBeat();

};
#endif
