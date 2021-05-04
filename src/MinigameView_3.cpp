#include "MinigameView_3.h"
#include "Animation.h"
#include <string>

MinigameView_3::MinigameView_3(std::shared_ptr<MinigameLogic_3> MinigameLogic_3,
                               std::shared_ptr<sf::RenderWindow> app) {
    this->miniLogic = MinigameLogic_3;
    this->app = app;

    if (!knifeTexture.loadFromFile("../data/art/knife.png")) {
        std::cout << "Could not load knife texture." << std::endl;
    }

    knifeSprite.setTexture(knifeTexture);
    knifeSprite.setTextureRect(sf::IntRect(0, 0, 28, 390));
    knifeSprite.setScale(sf::Vector2f(1.5, 1.3));
    knifeSprite.setPosition(this->miniLogic->getKnifePos());

    // Load all backgrounds
    if (!backgroundTexture1.loadFromFile("../data/art/background_round1.jpeg")) {
        std::cout << "Could not load background." << std::endl;
    }

    if (!backgroundTexture2.loadFromFile("../data/art/background_round2.jpeg")) {
        std::cout << "Could not load background." << std::endl;
    }

    if (!backgroundTexture3.loadFromFile("../data/art/background_round3.png")) {
        std::cout << "Could not load background." << std::endl;
    }

    if (!backgroundTexture4.loadFromFile("../data/art/background_round4.jpeg")) {
        std::cout << "Could not load background." << std::endl;
    }

    //load sushi texture
    if (!sushiTexture.loadFromFile("../data/art/sushi.png")) {
        std::cout << "Could not load sushi sprite sheet." << std::endl;
    }

    //load cut sushi texture
    if (!cutSushiTexture.loadFromFile("../data/art/cut_sushi.png")) {
        std::cout << "Could not load sushi sprite sheet." << std::endl;
    }

    //set up satsana animation
    if (!satsanaTexture.loadFromFile("../data/art/SatsanaSheet.png")) {
        std::cout << "Could not load Satsana sprite sheet." << std::endl;
    }
    satsanaSprite.setTexture(satsanaTexture);
    satsanaSprite.setPosition(10, 10);

    animation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, false);
    outcome.setFont(font);
    outcome.setCharacterSize(48);
    outcome.setFillColor(sf::Color::White);
    outcome.setPosition(sf::Vector2f(115, 20));

    //set up score text
    if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }

    //set up conveyor belt animation
    if (!beltTexture.loadFromFile("../data/art/spritesheet.png")) {
        std::cout << "Could not load belt sprite sheet." << std::endl;
    }
    beltSprite.setTexture(beltTexture);
    beltSprite.setPosition(-350, 550);
    beltSprite.setScale(sf::Vector2f(8, 2.5));

    beltAnimation = std::make_shared<Animation>(beltSprite, 0, 24, 235, 59, miniLogic->getBeltSpeed(), true);

    this->scoreText.setFont(font);
    this->scoreText.setCharacterSize(50);
    this->scoreText.setFillColor(sf::Color::Red);
    this->scoreText.setPosition(980, 10);
}

void MinigameView_3::drawBackground(const int &backgroundNum) {
    sf::RectangleShape background(
            sf::Vector2f(static_cast<float>(this->app->getSize().x), static_cast<float>(this->app->getSize().y)));

    switch (backgroundNum) {
        const sf::Texture *pBackgroundTexture;
        case 0:
            pBackgroundTexture = &backgroundTexture1;
            background.setTexture(pBackgroundTexture);
            break;
        case 1:
            pBackgroundTexture = &backgroundTexture2;
            background.setTexture(pBackgroundTexture);
            break;
        case 2:
            pBackgroundTexture = &backgroundTexture3;
            background.setTexture(pBackgroundTexture);
            break;
        default:
            pBackgroundTexture = &backgroundTexture4;
            background.setTexture(pBackgroundTexture);
            break;
    }

    app->draw(background);
}

void MinigameView_3::draw(const float &deltaTime, const float &round) {
    app->clear(sf::Color(193, 148, 126));

    // Draw the background
    drawBackground(round);

    //animate satsana
    animation->animate(outcome, deltaTime, app);

    //animate the belt
    beltAnimation->animate(deltaTime, app);

    //draw the food
    updateBeatBoxes(this->miniLogic->getBeatBoxes(), this->miniLogic->getPassedBoxes(), this->miniLogic->getCutBoxes());

    //draw the knife
    app->draw(knifeSprite);

    //draw the score
    app->draw(scoreText);


}

void MinigameView_3::updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes,
                                     const std::vector<BeatBoxLogic> &passedBoxes,
                                     const std::vector<BeatBoxLogic> &cutBoxes) {

    for (BeatBoxLogic beatBox : beatBoxes) {
        sf::Sprite sprite;
        sprite.setTexture(sushiTexture);
        sprite.setTextureRect(sf::IntRect(0, 0, 150, 75));
        sprite.setScale(this->miniLogic->getIngredientDim() / 75.0f);
        sprite.setPosition(beatBox.getCurPos().x - this->miniLogic->getIngredientDim().x / 2,
                           beatBox.getCurPos().y - this->miniLogic->getIngredientDim().y / 2);
        app->draw(sprite);
    }

    for (BeatBoxLogic beatBox : passedBoxes) {
        sf::Sprite sprite;
        sprite.setTexture(sushiTexture);
        sprite.setTextureRect(sf::IntRect(0, 0, 150, 75));
        sprite.setScale(this->miniLogic->getIngredientDim() / 75.0f);
        sprite.setPosition(beatBox.getCurPos().x - this->miniLogic->getIngredientDim().x / 2,
                           beatBox.getCurPos().y - this->miniLogic->getIngredientDim().y / 2);
        app->draw(sprite);
    }

    for (BeatBoxLogic beatBox : cutBoxes) {
        sf::Sprite sprite;
        sprite.setTexture(cutSushiTexture);
        sprite.setTextureRect(sf::IntRect(0, 0, 75, 75));
        sprite.setScale(this->miniLogic->getIngredientDim() / 75.0f);
        sprite.setPosition(beatBox.getCurPos().x - this->miniLogic->getIngredientDim().x / 2,
                           beatBox.getCurPos().y - this->miniLogic->getIngredientDim().y / 2);
        app->draw(sprite);
    }

}

void MinigameView_3::splitBox(const float &deltaTime) {

    if (!moving) {
        move = true;
        moving = true;
    }


}


void MinigameView_3::update(const float &deltaTime, const float &round) {
    this->miniLogic->updateBeatBoxes(deltaTime);
    this->miniLogic->updateCut(deltaTime);
    this->miniLogic->updatePassed(deltaTime);

    float x = this->miniLogic->getKnifePos().x;
    float y = this->miniLogic->getKnifePos().y;

    //if we need to move up
    if (move) {
        if (this->miniLogic->getKnifePos().y >= 150) {
            sf::Vector2f up(x, y - this->miniLogic->getKnifeSpeed() * deltaTime);
            this->miniLogic->setKnifePos(up);
            //if we reach the peak set move = false so knife goes down
            if (this->miniLogic->getKnifePos().y <= 150) {
                move = false;
            }
        }
    }

        //we need to move down
    else {
        if (this->miniLogic->getKnifePos().y < 500) {
            sf::Vector2f down(x, y + this->miniLogic->getKnifeSpeed() * deltaTime);
            this->miniLogic->setKnifePos(down);
        } else {
            moving = false;
        }
    }

    this->scoreText.setString("Score: " + std::to_string(this->miniLogic->getScore()));
    knifeSprite.setPosition(this->miniLogic->getKnifePos());

    draw(deltaTime, round);

}

void MinigameView_3::animatePostHit(const int &hitOutcome, int round, const float &deltaTime) {

    outcome.setString(outcomes[round][hitOutcome]);
    animation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, false);

}