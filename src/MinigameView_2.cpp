#include "MinigameView_2.h"
#include "constants.h"
#include "Animation.h"

MinigameView_2::MinigameView_2(std::shared_ptr<MinigameLogic_2> MinigameLogic_2, std::shared_ptr<sf::RenderWindow> app)
{
    //Retrieve logic and window
    miniLogic = MinigameLogic_2;
    this->app = app;

    if (!pizzaTexture.loadFromFile("../data/art/pizza.png")) {
        std::cout << "Could not load pizza sprite." << std::endl;
    }

    //Instantiate pizza object
    cPizza.setTexture(&pizzaTexture, true);
    cPizza.setRadius(MinigameLogic_2->getPRadius());
    cPizza.setOrigin(MinigameLogic_2->getPRadius(), MinigameLogic_2->getPRadius());
    cPizza.setPosition(MinigameLogic_2->getPosition());

    //retrieve knife sprite
    if(!knifeTexture.loadFromFile("../data/art/knife.png")){
        std::cout << "Could not load knife texture." << std::endl;
    }
    //Instantiate knife object
    knifeSprite.setTexture(knifeTexture);
    knifeSprite.setTextureRect(sf::IntRect(0, 0, 28, 390));
    knifeSprite.setScale(sf::Vector2f(1.5, 1.3));
    knifeSprite.setPosition(this->miniLogic->getKnifePos());
    knifeSprite.setRotation(270);
    //load in the font for result text
    if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }

    //Build baseCutShape, default angle is 0
    baseCut.setFillColor(sf::Color::Black);
    baseCut.setSize(sf::Vector2f(1.25f * MinigameLogic_2->getPRadius(), 2.0f));
    baseCut.setOrigin(0.0f, 1.0f/2.f);
    baseCut.setPosition(MinigameLogic_2->getPosition()); //set position

}

void MinigameView_2::draw()
{
  app->clear(sf::Color(193, 148, 126));

  //DRAW CUTS REMAINING TEXT
  sf::Text cutText;
  cutText.setFont(font);
  cutText.setCharacterSize(50);
  cutText.setFillColor(sf::Color::Black);
  cutText.setString("REMAINING CUTS: \n" + std::to_string(miniLogic->getMaxCuts() - playerCuts.size()));
  app->draw(cutText);

  // DRAW THE PIZZA
  app->draw(cPizza);

  // DRAW THE KNIFE
  knifeSprite.setPosition(miniLogic->getKnifePos());
  app->draw(knifeSprite);

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
  for(sf::RectangleShape cut: playerCuts)
  {
      if(miniLogic->getPAngle() < 2 * PI)
      {
        cut.setRotation(cut.getRotation() - miniLogic->getPAngle() * 180.f/PI);
        cPizza.setRotation(playerCuts[0].getRotation() - miniLogic->getPAngle() * 180.f/PI);
      }
      app->draw(cut);
  }
  //DrAW POST GAME
  if(miniLogic->state == MinigameLogic_2::gameState::ENDING) {
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(75);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(100,300);

    std::string scoreMsg = "SCORE:  " + std::to_string(miniLogic->getScore());
    scoreText.setString(scoreMsg);
    app->draw(scoreText);

    if(miniLogic->getRank() != "F")
      scoreMsg = "  RANK:  " + miniLogic->getRank();
    else
      scoreMsg = " You failed";

    scoreText.setPosition(100, 400);
    scoreText.setString(scoreMsg);
    app->draw(scoreText);

    if(miniLogic->getRank() != "F")
      scoreText.setString("Press Spacebar to continue");
    else
      scoreText.setString("Press Spacebar to try again");
    scoreText.setPosition(250,600);
    app->draw(scoreText);
  }

  if(playerCuts.size() == 0) {
    sf::Text startText;
    startText.setFont(font);
    startText.setCharacterSize(50);
    startText.setFillColor(sf::Color::Black);
    startText.setString("Listen to the following beat. After listening,\n hit space to begin cutting\n or Enter to replay the beat.");
    startText.setPosition(500,0);
    app->draw(startText);
  }
  app->display();
  //sleep here to prevent beat from playing before drawing
  sf::Time time = sf::seconds(0.001f);
  sf::sleep(time);
  if(miniLogic->getAngleSpeed() == 0) { miniLogic->playBeat(*app); }
}
void MinigameView_2::update(const float& deltaTime)
{
    app->clear();
    std::vector<float> cutAngles = miniLogic->getCutAngles();
    //if we need to move up
    if(cutAngles.size() < miniLogic->getMaxCuts() && miniLogic->getPAngle() < 2 * PI)
    {
        float x = miniLogic->getKnifePos().x;
        float y = miniLogic->getKnifePos().y;
        if(move){
            if(x >= cPizza.getPosition().x){
                sf::Vector2f left(x - miniLogic->getKnifeSpeed() * deltaTime, y);
                miniLogic->setKnifePos(left);
                //if we reach the peak set move = false so knife goes down
                if(miniLogic->getKnifePos().x <= cPizza.getPosition().x){
                    move = false;
                }
            }
        }
        //we need to move down
        else{
            if(x < cPizza.getPosition().x + 1.5f * cPizza.getRadius()){
                sf::Vector2f right(x + miniLogic->getKnifeSpeed() * deltaTime, y);
                miniLogic->setKnifePos(right);
            }
        }
    }
    draw();
}
