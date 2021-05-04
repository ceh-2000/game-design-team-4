#include "MinigameView_1.h"
#include "Animation.h"

MinigameView_1::MinigameView_1(std::shared_ptr<MinigameLogic_1> miniLogic, std::shared_ptr<sf::RenderWindow> app) {
    this->app = app;
    this->miniLogic = miniLogic;
    this->rectangle.setSize(sf::Vector2f(this->miniLogic->getBowlSize().x * 2, this->miniLogic->getBowlSize().y * 3.5));

    // Load all ingredient textures
    if (!appleTexture.loadFromFile("../data/art/apple.png")) {
        std::cout << "Could not load apple sprite sheet." << std::endl;
    }

    if (!mouseTexture.loadFromFile("../data/art/deadmouse.png")) {
        std::cout << "Could not load apple sprite sheet." << std::endl;
    }

    // Load bowl texture
    if (!bowlTexture.loadFromFile("../data/art/Bowl.png")) {
        std::cout << "Could not load apple sprite sheet." << std::endl;
    }

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

    // Load in the font for result text
    if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }
    this->scoreText.setFont(font);
    this->scoreText.setCharacterSize(50);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setPosition(this->app->getSize().x - 230, this->app->getSize().y - 125);

    this->instructionsText.setFont(font);
    this->instructionsText.setCharacterSize(40);
    this->instructionsText.setFillColor(sf::Color::Red);
    this->instructionsText.setPosition(120 , 80);
    this->instructionsText.setString("Press the right \nand left arrows \nto avoid dead mice \nand collect apples.");

    // Set up satsana animation
    if (!satsanaTexture.loadFromFile("../data/art/SatsanaSheet.png")) {
        std::cout << "Could not load Satsana sprite sheet." << std::endl;
    }
    satsanaSprite.setTexture(satsanaTexture);
    satsanaSprite.setPosition(0, this->app->getSize().y - 150);

    satsanaAnimation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, false);
    outcome.setFont(font);
    outcome.setCharacterSize(48);
    outcome.setFillColor(sf::Color::White);
    outcome.setPosition(sf::Vector2f(105, this->app->getSize().y - 125));
}

void MinigameView_1::drawBackground(const int &backgroundNum) {
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

void MinigameView_1::drawBowl() {
    this->rectangle.setPosition(this->miniLogic->getBowlPosition());
    const sf::Texture *pBackgroundTexture = &bowlTexture;
    rectangle.setTexture(pBackgroundTexture);
    app->draw(this->rectangle);
}

/*
Redraw all of our current beat boxes
*/
void MinigameView_1::drawBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes) {
    std::vector<bool> isGoodVector = this->miniLogic->getIsGoodVector();
    int counter = 0;
    for (BeatBoxLogic beatBox : beatBoxes) {
        sf::Sprite sprite;

        bool isGood = isGoodVector.at(counter);
        if (isGood) {
            sprite.setTexture(appleTexture);
        } else {
            sprite.setTexture(mouseTexture);
        }

        sprite.setTextureRect(sf::IntRect(150, 0, 50, 50));
        sprite.setScale(this->miniLogic->getIngredDim() / 50.0f);
        sprite.setPosition(beatBox.getCurPos().x - this->miniLogic->getIngredDim().x / 2,
                           beatBox.getCurPos().y - this->miniLogic->getIngredDim().y / 2);
        app->draw(sprite);

        counter++;
    }
}

void MinigameView_1::drawStatic() {
    float beatBoxEnd = this->miniLogic->getBeatBoxes().at(0).getEndPos().y + this->miniLogic->getIngredDim().y / 2.0f;
    sf::RectangleShape line(sf::Vector2f(app->getSize().x, 10.0f));
    line.setPosition(sf::Vector2f(0.0f, beatBoxEnd - 60.0f));
    line.setFillColor(sf::Color::Black);
    app->draw(line);
    app->draw(instructionsText);
}

void MinigameView_1::drawScore(int score) {
    this->scoreText.setString("Score: " + std::to_string(score));
    app->draw(scoreText);
}

void MinigameView_1::update(const float &deltaTime, const int &round) {
    app->clear(sf::Color(193, 148, 126));

    drawBackground(round);
    drawBowl();
    drawBeatBoxes(this->miniLogic->getBeatBoxes());
    drawScore(this->miniLogic->getScore());
    drawStatic();
    satsanaAnimation->animate(outcome, deltaTime, app);
}

void MinigameView_1::animatePostHit(const int &hitOutcome, int round, const float &deltaTime) {

    outcome.setString(outcomes[round][hitOutcome]);
    satsanaAnimation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, false);

}

