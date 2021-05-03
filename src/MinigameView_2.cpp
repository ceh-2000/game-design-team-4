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

    //load in the font for result text
    if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }
    //Instantiate pizza object
    cPizza.setTexture(&pizzaTexture, true);
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
    knifeBox.setFillColor(sf::Color::Black);

    //set up satsana animation
    if(!satsanaTexture.loadFromFile("../data/art/SatsanaSheet.png")){
        std::cout << "Could not load Satsana sprite sheet." << std::endl;
    }
    satsanaSprite.setTexture(satsanaTexture);
    satsanaSprite.setPosition(10,680);

    satsanaAnimation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, false);
    outcome.setFont(font);
    outcome.setCharacterSize(48);
    outcome.setFillColor(sf::Color::White);
    outcome.setPosition(sf::Vector2f(115, 680));
}

void MinigameView_2::draw()
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
  knifeBox.setPosition(miniLogic->getKnifePos());
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
  if(miniLogic->state == MinigameLogic_2::gameState::ENDING) {
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setString("SCORE:  " + std::to_string(miniLogic->getScore()) + "  RANK:  " + miniLogic->getRank());
    scoreText.setPosition(550,650);

    app->draw(scoreText);
    scoreText.setString("Press Spacebar to continue");
    scoreText.setPosition(550,700);
    app->draw(scoreText);
  }

  if(playerCuts.size() == 0) {
    sf::Text startText;
    startText.setFont(font);
    startText.setCharacterSize(50);
    startText.setFillColor(sf::Color::Red);
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
    //app->clear();
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
    
    satsanaAnimation->animate(outcome, deltaTime, app);
    draw();
}

void MinigameView_2::animatePostHit(const int& hitOutcome, int round, const float& deltaTime){
    
    outcome.setString(outcomes[round][hitOutcome]);
    satsanaAnimation = std::make_shared<Animation>(satsanaSprite, 0, 3, 128, 128, 0.25, false);

}
