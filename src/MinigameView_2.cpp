#include "MinigameView_2.h"
#include "constants.h"

MinigameView_2::MinigameView_2(std::shared_ptr<MinigameLogic_2> MinigameLogic_2, std::shared_ptr<sf::RenderWindow> app)
{
    //Retrieve logic and window
    this->miniLogic = MinigameLogic_2;
    this->app = app;

    if (!pizzaTexture.loadFromFile("../data/art/pizza.png")) {
        std::cout << "Could not load pizza sprite." << std::endl;
    }

    //load in the font for result text
    if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }
    //Instantiate pizza object
    cPizza.setTexture(&pizzaTexture, true);
    cPizza.setRadius(MinigameLogic_2->getPRadius());
    cPizza.setOrigin(MinigameLogic_2->getPRadius(), MinigameLogic_2->getPRadius());
    cPizza.setPosition(MinigameLogic_2->getPosition());

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
    knifeBox.setFillColor(sf::Color::Black);
}

void MinigameView_2::drawPlay()
{
    app->clear(sf::Color::Blue);

    //DRAW CUTS REMAINING TEXT
    sf::Text cutText;
    cutText.setFont(font);
    cutText.setCharacterSize(50);
    cutText.setFillColor(sf::Color::Red);
    cutText.setString("REMAINING CUTS: \n" + std::to_string(miniLogic->getMaxCuts() - playerCuts.size()));
    app->draw(cutText);
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
    for(sf::RectangleShape cut: playerCuts)
    {
        if(miniLogic->getPAngle() < 2 * PI)
        {
          cut.setRotation(cut.getRotation() - miniLogic->getPAngle() * 180.f/PI);
          cPizza.setRotation(playerCuts[0].getRotation() - miniLogic->getPAngle() * 180.f/PI);
        }
        app->draw(cut);
    }

    if(this->miniLogic->state == MinigameLogic_2::gameState::ENDING || this->miniLogic->state == MinigameLogic_2::gameState::STOPPED) {
      sf::Text scoreText;
      scoreText.setFont(font);
      scoreText.setCharacterSize(50);
      scoreText.setFillColor(sf::Color::Red);
      scoreText.setString("SCORE:  " + std::to_string(this->miniLogic->getScore()));
      scoreText.setPosition(550,650);

      app->draw(scoreText);
      scoreText.setString("Press Spacebar to continue");
      scoreText.setPosition(550,700);
      app->draw(scoreText);
      this->miniLogic->state = MinigameLogic_2::gameState::STOPPED;
    }
    if(playerCuts.size() == 0) {
      sf::Text startText;
      startText.setFont(font);
      startText.setCharacterSize(50);
      startText.setFillColor(sf::Color::Red);
      startText.setString("Listen to the following beat. After listening,\n hit space to begin cutting\n or Enter to replay the beat.");
      startText.setPosition(500,50);
      app->draw(startText);
    }
    app->display();
    //sleep here to prevent beat from playing before drawing
    sf::Time time = sf::seconds(0.001f);
    sf::sleep(time);
    if(miniLogic->getAngleSpeed() == 0) { miniLogic->playBeat(*app); }
}

void MinigameView_2::drawEndGame() {
}
void MinigameView_2::update(const float& deltaTime)
{
  app->clear();
  std::vector<float> cutAngles = miniLogic->getCutAngles();
  //if we need to move up
  if(cutAngles.size() < miniLogic->getMaxCuts() && miniLogic->getPAngle() < 2 * PI)
  {
      float x = this->miniLogic->getKnifePos().x;
      float y = this->miniLogic->getKnifePos().y;
      if(moveKnife){
          if(x >= cPizza.getPosition().x){
              sf::Vector2f left(x - this->miniLogic->getKnifeSpeed() * deltaTime, y);
              this->miniLogic->setKnifePos(left);
              //if we reach the peak set move = false so knife goes right
              if(this->miniLogic->getKnifePos().x <= cPizza.getPosition().x){
                  moveKnife = false;
              }
          }
      }

          //we need to move right
      else{
          if(x < cPizza.getPosition().x + 1.5f * cPizza.getRadius()){
              sf::Vector2f right(x + this->miniLogic->getKnifeSpeed() * deltaTime, y);
              this->miniLogic->setKnifePos(right);
          }
      }
  }
  drawPlay();
}
