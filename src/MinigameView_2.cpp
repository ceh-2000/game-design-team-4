#include "MinigameView_2.h"
#include "constants.h"

MinigameView_2::MinigameView_2(std::shared_ptr<MinigameLogic_2> MinigameLogic_2, std::shared_ptr<sf::RenderWindow> app)
{
  //Retrieve logic and window
	this->miniLogic = MinigameLogic_2;
  this->app = app;

  //Instantiate pizza object
  cPizza.setRadius(MinigameLogic_2->getPRadius());
  cPizza.setOrigin(MinigameLogic_2->getPRadius(), MinigameLogic_2->getPRadius());
  cPizza.setPosition(MinigameLogic_2->getPosition());
  cPizza.setFillColor(sf::Color(255.f,165.f,0.0f));

  //Build baseCutShape, default angle is 0
  baseCut.setFillColor(sf::Color::Red);
  baseCut.setSize(sf::Vector2f(1.25f * MinigameLogic_2->getPRadius(), 1.0f));
  baseCut.setOrigin(0.0f, 1.0f/2.f);
  baseCut.setPosition(MinigameLogic_2->getPosition()); //set position

	//load knife texture
  knifeBox.setSize(sf::Vector2f(200, 25));
  //knifeBox.setTexture(this->knife.getTexture());
	//knifeBox.setOrigin(knifeBox.getSize()/2.f);
	knifeBox.setPosition(MinigameLogic_2->getPosition());
	//knifeBox.move(1.5 * cPizza.getRadius(), 200);
	knifeBox.setFillColor(sf::Color::Black);
}

void MinigameView_2::draw()
{
  app->clear(sf::Color::Blue);

  // DRAW THE PIZZA
  app->draw(cPizza);

	// DRAW THE KNIFE
	knifeBox.setPosition(this->miniLogic->getKnifePos());
	app->draw(knifeBox);

  //DRAWING THE CUTS
	std::vector<float> cutAngles = miniLogic->getCutAngles();
	//if we made a cut, push in the base model transformed to right pos
  if(cutAngles.size() > playerCuts.size())
  {
    sf::RectangleShape newRect = baseCut;
    //negative ensures
    newRect.setRotation(cutAngles[cutAngles.size()-1] * 180.f/PI);
    playerCuts.push_back(newRect);
  }
  //std::cout << "cut angles larger than number of rects? " << cutAngles().size() << "\n";
	if(cutAngles.size() < miniLogic->getMaxCuts() && miniLogic->getPAngle() < 2 * PI)
		cPizza.rotate(-miniLogic->getPAngle() * 180.f/PI); //
	for(sf::RectangleShape cut: playerCuts)
	{
		if(miniLogic->getPAngle() < 2 * PI)
			cut.setRotation(cut.getRotation() - miniLogic->getPAngle() * 180.f/PI);
		app->draw(cut);
	}

  app->display();
}


void MinigameView_2::cutPizza(const float& deltaTime)
{
	move = true;
}

void MinigameView_2::update(const float& deltaTime)
{
	std::vector<float> cutAngles = miniLogic->getCutAngles();
 //if we need to move up
 if(cutAngles.size() < miniLogic->getMaxCuts() && miniLogic->getPAngle() < 2 * PI)
 {
	 float x = this->miniLogic->getKnifePos().x;
 	 float y = this->miniLogic->getKnifePos().y;
	  if(move){
		 	 if(x >= cPizza.getPosition().x){
		 			 sf::Vector2f left(x - this->miniLogic->getKnifeSpeed() * deltaTime, y);
					 this->miniLogic->setKnifePos(left);
					 //if we reach the peak set move = false so knife goes down
					 if(this->miniLogic->getKnifePos().x <= cPizza.getPosition().x){
							 move = false;
					 }
			 }
	 }

	 //we need to move down
	 else{
			 if(x < cPizza.getPosition().x + 1.5f * cPizza.getRadius()){
					sf::Vector2f right(x + this->miniLogic->getKnifeSpeed() * deltaTime, y);
					this->miniLogic->setKnifePos(right);
			 }
	 }
 }
  draw();
}
