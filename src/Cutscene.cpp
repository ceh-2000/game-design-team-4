#include "Cutscene.h"

Cutscene::Cutscene(std::shared_ptr<sf::RenderWindow> app) {
    this->app = app;

    font.loadFromFile("../data/fonts/orange_kid.ttf");
    this->scoreText = sf::Text("", font, 50);
    this->scoreText.setFillColor(sf::Color::White);

    this->chefText = sf::Text("", font, 50);
    this->chefText.setFillColor(sf::Color::White);

    satsanaTexture.loadFromFile("../data/art/SatsanaSheet.png");
    satsanaSprite.setTexture(satsanaTexture);
    satsanaSprite.setPosition(0, 640);

    satsanaAnimation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, true);
}

void Cutscene::draw(const int &cutsceneNum) {
    this->app->clear(sf::Color::Black);
    this->app->draw(background);
    if (cutsceneNum == 1) {
        this->app->draw(mainCharacter);
        this->app->draw(otherCharacter);
    }
    this->app->draw(dialogueBox);
    if (cutsceneNum == 1) {
        this->app->draw(scoreText);
    } else {
        this->app->draw(chefText);
    }
}

void Cutscene::update(const float &dt, const int &cutSceneNum) {

    if (dialogueStrIter < dialogueStr.length() && cutSceneNum == 1) {
        if (elapsedTime > 0.05f) {
            this->scoreText.setString(scoreText.getString() + dialogueStr[dialogueStrIter]);
            dialogueStrIter++;
            elapsedTime = 0;
        }
        elapsedTime += dt;
    } else if (chefStrIter < chefStr.length() && cutSceneNum == 2) {
        if (elapsedTime > 0.05f) {
            this->chefText.setString(chefText.getString() + chefStr[chefStrIter]);
            chefStrIter++;
            elapsedTime = 0;
        }
        elapsedTime += dt;
    }
    draw(cutSceneNum);
    satsanaAnimation->animate(dt, app);
    this->app->display();
}

void Cutscene::selectCutscene(const int &cutSceneNum) {

    switch (cutSceneNum) {
        case 1:
            backgroundTexture.loadFromFile("../data/art/background.png");
            mcTexture.loadFromFile("../data/art/mc-cutscene.png");
            otherCharacterTexture.loadFromFile("../data/art/male-chef.png");
            dialogueBoxTexture.loadFromFile("../data/art/dialogueBox.png");
            dialogueStr = "Hi " + this->name + "! " + "Current rank is " + this->rank + ".\nPress [SPACE BAR] to ";
            if (this->rank != "F")
                dialogueStr += "skip.";
            else
                dialogueStr += "try round again.";
            background.setTexture(backgroundTexture);
            mainCharacter.setTexture(mcTexture);
            otherCharacter.setTexture(otherCharacterTexture);
            dialogueBox.setTexture(dialogueBoxTexture);
            otherCharacter.setPosition(800, 0);
            dialogueBox.setPosition(0, 600);
            scoreText.setPosition(125, 625);
            break;
        case 2:
            if (chefName == "Guy Fieri") {
                backgroundTexture.loadFromFile("../data/art/guy.png");
                chefStr = "Hi " + this->name + "! " + "You made it to ~flavor~ town.\nPress [SPACE BAR] to skip.";

            } else if (chefName == "Bobby Flay") {
                backgroundTexture.loadFromFile("../data/art/bobby_flay.png");
                chefStr = "Hi " + this->name + "! " + "You beat Bobby Flay.\nPress [SPACE BAR] to skip.";

            } else if ("Gordon Ramsay") {
                backgroundTexture.loadFromFile("../data/art/gordon.png");
                chefStr = "Hi " + this->name + "! " +
                          "It doesn't look fantastic... but it tastes delicious.\nPress [SPACE BAR] to skip.";
            }
            background.setTexture(backgroundTexture);
            chefText.setPosition(125, 625);
    }
}
