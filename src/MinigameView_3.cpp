#include "MinigameView_3.h"
#include "Animation.h"
#include <string>

MinigameView_3::MinigameView_3(std::shared_ptr<MinigameLogic_3> MinigameLogic_3, std::shared_ptr<sf::RenderWindow> app)
{
	this->miniLogic = MinigameLogic_3;
	this->app = app;

	//load knife texture
    knifeBox.setSize(sf::Vector2f(25, 200));
    //knifeBox.setTexture(this->knife.getTexture());
	knifeBox.setFillColor(sf::Color::Black);
    knifeBox.setPosition(this->miniLogic->getKnifePos());

	//load sushi texture
    if (!sushiTexture.loadFromFile("../data/art/sushi.png")) {
        std::cout << "Could not load sushi sprite sheet." << std::endl;
    }

    //set up satsana animation
    if(!satsanaTexture.loadFromFile("../data/art/SatsanaSheet.png")){
        std::cout << "Could not load Satsana sprite sheet." << std::endl;
    }
    satsanaSprite.setTexture(satsanaTexture);
    satsanaSprite.setPosition(10,10);

    animation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.3, true);

    //set up score text
    if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }

    //set up conveyor belt animation
    if(!beltTexture.loadFromFile("../data/art/spritesheet.png")){
        std::cout << "Could not load belt sprite sheet." << std::endl;
    }
    beltSprite.setTexture(beltTexture);
    beltSprite.setPosition(-350, 400);
    beltSprite.setScale(sf::Vector2f(8, 2.5));

    beltAnimation = std::make_shared<Animation>(beltSprite, 0, 24, 235, 59, 0.011, true);

    this->scoreText.setFont(font);
    this->scoreText.setCharacterSize(50);
    this->scoreText.setFillColor(sf::Color::Red);
    this->scoreText.setPosition(980, 10);
}



void MinigameView_3::draw(const float& deltaTime){

    //animate satsana
    animation->animate(deltaTime, app);

    //animate the belt
    beltAnimation->animate(deltaTime, app);

    //draw the food
    updateBeatBoxes(this->miniLogic->getBeatBoxes());

    //draw the knife
    app->draw(knifeBox);

    //draw the score
    app->draw(scoreText);



}

void MinigameView_3::updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes) {

    BeatBoxLogic lastBox = beatBoxes.back();
    sf::Vector2f newPos = lastBox.getCurPos();
    newPos.x += 20;

    for (BeatBoxLogic beatBox : beatBoxes) {
            sf::Sprite sprite;
            sprite.setTexture(sushiTexture);
            sprite.setTextureRect(sf::IntRect(0, 0, 150, 75));
            sprite.setScale(this->miniLogic->getIngredientDim()/75.0f);
            sprite.setPosition(beatBox.getCurPos().x-this->miniLogic->getIngredientDim().x/2, beatBox.getCurPos().y-this->miniLogic->getIngredientDim().y/2);
            app->draw(sprite);
    }

    cutBoxes.push_back(BeatBoxLogic(lastBox.getCurPos(),
                                         lastBox.getPostHitPos(),
                                         lastBox.getPostHitPos(),
                                         lastBox.getVelocity(), lastBox.getSongTime()));

    cutBoxes.push_back(BeatBoxLogic(newPos,
                                         lastBox.getPostHitPos(),
                                         lastBox.getPostHitPos(),
                                         lastBox.getVelocity(), lastBox.getSongTime()));

    for (BeatBoxLogic beatBox : cutBoxes) {
            sf::Sprite sprite;
            sprite.setTexture(sushiTexture);
            sprite.setTextureRect(sf::IntRect(0, 0, 150, 75));
            sprite.setScale(this->miniLogic->getIngredientDim()/75.0f);
            sprite.setPosition(beatBox.getCurPos().x-this->miniLogic->getIngredientDim().x/2, beatBox.getCurPos().y-this->miniLogic->getIngredientDim().y/2);
            app->draw(sprite);
    }

    
}

void MinigameView_3::splitBox(const float& deltaTime){

    move = true;

    //TODO: Split the boxes based on the time that the user pressed

}


void MinigameView_3::update(const float& deltaTime){
    this->miniLogic->updateBeatBoxes(deltaTime);
 
    float x = this->miniLogic->getKnifePos().x;
    float y = this->miniLogic->getKnifePos().y;

    //if we need to move up
    if(move){
        //std::cout << "MOVE";
        if(this->miniLogic->getKnifePos().y >= 150){
            sf::Vector2f up(x, y - this->miniLogic->getKnifeSpeed() * deltaTime);
            this->miniLogic->setKnifePos(up);
            //if we reach the peak set move = false so knife goes down
            if(this->miniLogic->getKnifePos().y <= 150){
                move = false;
            }
        }
    }

    //we need to move down
    else{
        if(this->miniLogic->getKnifePos().y < 600){
             sf::Vector2f down(x, y + this->miniLogic->getKnifeSpeed() * deltaTime);
            this->miniLogic->setKnifePos(down);
        }
    }

    std::cout << this->miniLogic->getKnifePos().y;
    std::cout << "\n";

    this->scoreText.setString("Score: " + std::to_string(this->miniLogic->getScore()));
    knifeBox.setPosition(this->miniLogic->getKnifePos());

	draw(deltaTime);

}
