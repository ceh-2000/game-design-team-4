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
}

void MinigameView_2::draw()
{
  app->clear();
  //app->draw(this->circle);
  //app->display();

    // DRAW THE PIZZA
  cPizza.rotate(-miniLogic->getPAngle() * 180.f/PI); //
  app->draw(cPizza);

  //DRAWING THE CUTS

  //if we made a cut, push in the base model transformed to right pos
  if(miniLogic->getCutAngles().size() > playerCuts.size())
  {
    sf::RectangleShape newRect = baseCut;
    //negative ensures
    newRect.setRotation(miniLogic->getCutAngles()[miniLogic->getCutAngles().size()-1] * 180.f/PI);
    playerCuts.push_back(newRect);
  }
  //std::cout << "cut angles larger than number of rects? " << miniLogic->getCutAngles().size() << "\n";
  if(miniLogic->getCutAngles().size() > 0)
  {
    for(sf::RectangleShape cut: playerCuts)
    {
      cut.setRotation(cut.getRotation() - miniLogic->getPAngle() * 180.f/PI);
      app->draw(cut);
    }
  }
  app->display();
}

void MinigameView_2::update(const float& deltaTime)
{
  draw();
}
