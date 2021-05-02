#include "MinigameLogic_2.h"
#include "constants.h"

MinigameLogic_2::MinigameLogic_2(std::shared_ptr<Song> song, int round)
{
    this->song = song;
    switch (round) {
      case 0:
        this->maxCuts = 8;
        break;
      case 1:
        this->maxCuts = 10;
        break;
      case 2:
        this->maxCuts = 15;
        break;
      case 3:
        this->maxCuts = 20;
        break;
      default:
        break;
    }
    position = sf::Vector2f(600, 400);
    knifePos = sf::Vector2f(position.x + 1.5 * pizzaRadius, position.y);
    goalAngle = 2 * PI/(float) maxCuts; //90 degrees
}
// Every hit of space adds new cut until reach max limit
void MinigameLogic_2::pushNewCut()
{
    //Add cut into the vector
    if(cutAngles.size() == 0){
        cutAngles.push_back(0.0f);
    }
    else if(cutAngles.size() > 0 && cutAngles.size() < maxCuts && pizzaAngle <= 2.0f * PI)
    {
        cutAngles.push_back(pizzaAngle);
    }

    std::cout << "cutAngles: ";
    for(int i=0; i < cutAngles.size(); i++)
        std::cout << cutAngles.at(i) << ' ';
    std::cout << "\n";
}

void MinigameLogic_2::update(float deltaTime)
{
    if(cutAngles.size() > 0 && cutAngles.size() < maxCuts){
        rotTime += deltaTime;
        pizzaAngle = angleSpeed * rotTime;
    }

    //If player ran out of cuts or made one revolution, calculate score
    if((cutAngles.size() == maxCuts || pizzaAngle >= 2.0f * PI) && gameScore < 0.0)
    {
        gameScore = calcScore();
        std::cout << "Game Score: " << gameScore << "\n";
    }
}

//TODO: CLEAN UP AND REFACTOR THIS CODE
//Play beat sequence
void MinigameLogic_2::playBeat(sf::RenderWindow &app)
{
  //Shift duration for higher cuts
  if(maxCuts >= 10) {
    song->setSoundPitch(2);
  }

  sf::Clock time;
  time.restart();

  int i = 0;
  while(i < maxCuts + 1)
  {
    if(song->getSoundStatus() == sf::Sound::Status::Stopped)
    {
      if(i != maxCuts) {
        song->playSound();
      }
      i++;
    }

  }
  revTime = time.restart().asSeconds();
  angleSpeed = 2 * PI/ revTime; //Angular speed: one rps; tot time determined by rhythm "call"

  //Clear the entire event queue: Prevents keyboard and mouse presses
  sf::Event event;
  while(app.pollEvent(event))
  {
    //Can put exceptions here if want to register certain events
  }
}
//Score calculating done at end of game
float MinigameLogic_2::calcScore()
{
    // Worst score that player can get given maxcut
    float worstScore = 200.f * (float)(maxCuts - 1) / (float) maxCuts;

    float score = 0.f;
    //calculate the total error for each pizza slice
    if(cutAngles.size() != 1)
    {
        for(int i=1; i < cutAngles.size() ; i++)
        {
            score += 100.f * abs((cutAngles[i] - cutAngles[i-1] - goalAngle))/goalAngle; //slice angle - expected angle
        }
    }
    //add in last slice from end to first cut
    score += 100.f *(float) abs((2 * PI - cutAngles.back() - goalAngle))/goalAngle;
    //Add error of missing slices
    if(cutAngles.size() < maxCuts){
        score +=  100.f * (maxCuts - cutAngles.size());
    }
    score = score / (float) maxCuts; //Average score of all slices
    //good scores are small, so operation makes 100 % best score
    this->state = MinigameLogic_2::gameState::ENDING;
    gameScore = 100 * (1 - score/worstScore);
    gradeMinigame();
    return gameScore;
}

std::string MinigameLogic_2::gradeMinigame() {
  float grade = gameScore;

  std::string letter_grade = " ";
  if(grade > 95 ) {
    letter_grade = "S";
  } else if (grade > 90) {
    letter_grade = "A";
  } else if (grade > 80) {
    letter_grade = "B";
  } else if (grade > 70) {
    letter_grade = "C";
  } else if (grade > 60) {
    letter_grade = "D";
  }
  this->grade = letter_grade;
  return letter_grade;
}
