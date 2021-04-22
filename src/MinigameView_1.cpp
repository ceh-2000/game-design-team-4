#include "MinigameView_1.h"

MinigameView_1::MinigameView_1(std::shared_ptr<MinigameLogic_1> miniLogic, std::shared_ptr<sf::RenderWindow> app)
{
    this->app = app;
    this->miniLogic = miniLogic;
    float scale = this->miniLogic->getBowlSize().x / this->miniLogic->getBowlSize().y;
    this->circle.setScale(scale, 1);
    this->circle.setPosition(this->miniLogic->getBowlPosition());

//    if (!texture.loadFromFile("../data/art/SatsanaSheet.png")) {
//        std::cout << "Could not load Satsana sprite sheet." << std::endl;
//    }
//
//    rectSourceSprite.left = 0;
//    rectSourceSprite.top = 0;
//    rectSourceSprite.width = 128;
//    rectSourceSprite.height = 128;

    //load in the font for result text
    if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }
    this->scoreText.setFont(font);
    this->scoreText.setCharacterSize(50);
    this->scoreText.setFillColor(sf::Color::Red);

}

void MinigameView_1::drawBowl()
{
    this->circle.setPosition(this->miniLogic->getBowlPosition());
    app->draw(this->circle);
}

/*
Redraw all of our current beat boxes
*/
void MinigameView_1::drawBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes) {
    std::vector<bool> isGoodVector = this->miniLogic->getIsGoodVector();
    int counter = 0;
    for (BeatBoxLogic beatBox : beatBoxes) {
        sf::RectangleShape box;
        box.setSize(this->miniLogic->getIngredDim());

        bool isGood = isGoodVector.at(counter);
        sf::Color color = sf::Color::Magenta;
        if(isGood == false){
            color = sf::Color::Black;
        }

        box.setFillColor(color);
        box.setPosition(beatBox.getCurPos().x-this->miniLogic->getIngredDim().x/2, beatBox.getCurPos().y-this->miniLogic->getIngredDim().y/2);
        app->draw(box);

        counter ++;
    }
}

void MinigameView_1::drawStatic(){
    float beatBoxEnd = this->miniLogic->getBeatBoxes().at(0).getEndPos().y + this->miniLogic->getIngredDim().y/2.0f;
    sf::RectangleShape line(sf::Vector2f(app->getSize().x, 2.0f));
    line.setPosition(sf::Vector2f(0.0f, beatBoxEnd));
    line.setFillColor(sf::Color::Black);
    app->draw(line);
}

void MinigameView_1::drawScore(int score) {
    this->scoreText.setString("Score: "+std::to_string(score));
    app->draw(scoreText);
}

void MinigameView_1::update(const float& deltaTime)
{
    app->clear(sf::Color(255, 165, 0, 1));

    drawBowl();
    drawBeatBoxes(this->miniLogic->getBeatBoxes());
    drawScore(this->miniLogic->getScore());
    drawStatic();
}


