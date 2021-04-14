#include "MinigameLogic_2.h"
#include "constants.h"

MinigameLogic_2::MinigameLogic_2(std::shared_ptr<Song> song, int maxCuts)
{
  this->song = song;

  this->maxCuts = maxCuts;
  goalAngle = 2 * PI/(float) maxCuts; //90 degrees
  angleSpeed = 2 * PI/ revTime; //Angular speed: one rps; tot time determined by rhythm "call"
}
// Every hit of space adds new cut until reach max limit
void MinigameLogic_2::pushNewCut()
{
  //Add cut into the vector
  //std::cout << "Cut made at angle: " << pizzaAngle << "\n";
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
    //std::cout << "Current Pizza Angle: " << logic.getPAngle() << "\n";
  }

  //If player ran out of cuts or made one revolution, calculate score
  if((cutAngles.size() == maxCuts || pizzaAngle >= 2.0f * PI) && gameScore == 0.0)
  {
    gameScore = calcScore();
    std::cout << "Game Score: " << gameScore << "\n";
  }
}

//Score calculating done at end of game
float MinigameLogic_2::calcScore()
{
  float score = 0.f;
  //calculate the total error for each pizza slice
  if(cutAngles.size() != 1){
    for(int i=1; i < cutAngles.size() ; i++){
      //std::cout << i + 1 << "th cut: " << cutAngles[i] - cutAngles[i-1] - goalAngle << "\n";
      score += abs(cutAngles[i] - cutAngles[i-1] - goalAngle); //slice angle - expected angle
    }
  }
  //if there are less than requisite cuts error added is size of missed slices
  if(cutAngles.size() < maxCuts){
    score += (maxCuts - cutAngles.size()) * goalAngle;
  }

  return score;
}
