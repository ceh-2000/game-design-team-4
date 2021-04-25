#include "MinigameView_3.h"
#include "Animation.h"

MinigameView_3::MinigameView_3(std::shared_ptr<MinigameLogic_3> MinigameLogic_3, std::shared_ptr<sf::RenderWindow> app)
{
	this->miniLogic = MinigameLogic_3;
	this->app = app;

	//load knife texture
    knifeBox.setSize(sf::Vector2f(25, 200));
    //knifeBox.setTexture(this->knife.getTexture());
	knifeBox.setFillColor(sf::Color::Black);

	//load vegetable texture

    satsanaTexture.loadFromFile("../data/art/SatsanaSheet.png");
    satsanaSprite.setTexture(satsanaTexture);
    satsanaSprite.setPosition(10,10);

    animation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.3, true);

	
}

void MinigameView_3::draw(){

    //draw the knife    
    knifeBox.setPosition(this->miniLogic->getKnifePos());
    app->draw(knifeBox);
    //app->draw(satsanaSprite);



}

void MinigameView_3::updateBeatBoxes(const std::vector<BeatBoxLogic> &beatBoxes) {
    for (BeatBoxLogic beatBox : beatBoxes) {
            sf::RectangleShape box;
            box.setSize(this->miniLogic->getIngredientDim());
            box.setFillColor(sf::Color::White);
            box.setPosition(beatBox.getCurPos());
            app->draw(box);
    }
}

void MinigameView_3::splitBox(const float& deltaTime){

    move = true;

    //TODO: Split the boxes based on the time that the user pressed


}


void MinigameView_3::update(const float& deltaTime){
    this->miniLogic->updateBeatBoxes(deltaTime);
    updateBeatBoxes(this->miniLogic->getBeatBoxes());

     float x = this->miniLogic->getKnifePos().x;
     float y = this->miniLogic->getKnifePos().y;

    //if we need to move up
    if(move){
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


    animation->animate(deltaTime, app);
	draw();

}
