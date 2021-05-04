#include "Song.h"
#include "json.h"
#include <iostream>
#include <fstream>
#include <string>
#include "constants.h"

Song::Song(std::vector<std::string> songFilePaths, std::vector<std::string> soundFilePaths)
{
  this->songFilePaths = songFilePaths;
  this->soundFilePaths = soundFilePaths;
  /*
  // Open music file and play music
  // We open instead of loading to use less memory
  if (!music.openFromFile(AUD_PATH_BASE + songFilePaths.at(0)))
    std::cout << "Could not load music." << std::endl;
  music.setVolume(40.0f); // Reduce music to 10%

  // Open sound effects
  if (!buffer.loadFromFile(AUD_PATH_BASE + soundFilePaths.at(0)))
    std::cout << "Could not load sound." << std::endl;
  sound.setBuffer(buffer);
  sound.setVolume(40.0f); // Reduce music to 10%
  sound.setPitch(1);

  // Read the json and get the timing vector
  std::ifstream i("../Rhythm_Charter/timingChart.json");
  nlohmann::json timingChart;
  i >> timingChart;

  timingChart.at("test").get_to(correctTimings);
  */
  //dummy vector of timings
  //correctTimings = {6.79, 8.62, 10.63, 12.65, 14.65, 16.59, 18.576, 22.52, 23.02, 23.56, 24.04, 24.54, 25.03, 25.53};
}

void Song::setGameStateAudio(int state, int round) {
  std::string pathAudio= "";
  //retrieve songs that the state uses
  for (auto file: songFilePaths) {
    int i = 1;
    //search file name for state marker
    while (file[i] != '_') {
      if ((int)file[i] - 48 == state) {
        pathAudio = file;
        if (!music.openFromFile(AUD_PATH_BASE + file + ".wav"))
          std::cout << "Could not load music." << std::endl;
        music.setVolume(40.0f); // Reduce music to 10%
      }
      i++;
    }
  }

  //retrieve sounds that the state uses
  for (auto file: soundFilePaths) {
    int i = 1;
    //search file name for state marker
    while (file[i] != '_') {
      if ((int)file[i] - 48 == state) {
        if (!buffer.loadFromFile(AUD_PATH_BASE + file))
          std::cout << "Could not load sound." << std::endl;
        sound.setBuffer(buffer);
        sound.setVolume(40.0f); // Reduce music to 10%
      }
      i++;
    }
  }

  //Retrieve song timings for minigames
  if(state > 0 && state < 5) {
    //If no user created songs were found
    if (pathAudio == "") {
      pathAudio = basicSongs[state-1];
      if (!music.openFromFile(AUD_PATH_BASE + basicSongs[state-1] + ".wav"))
        std::cout << "Could not load music." << std::endl;
      music.setVolume(40.0f); // Reduce music to 10%
    }
    // Read the json and get the timing vector
    std::ifstream i("../Rhythm_Charter/timingChart.json");
    nlohmann::json timingChart;
    i >> timingChart;
    //TODO: WHEN WE MAP THE TIMINGS HERE, NAME IS SAME AS SONG
    //timingChart.at("test").get_to(correctTimings);
    std::string json_elem;
    //get json element =audiofile - typeending
    for(int index = 0; index < pathAudio.size(); index ++) {
      json_elem.push_back(pathAudio[index]);
    }
    json_elem += std::to_string(round);
    timingChart.at(json_elem).get_to(correctTimings);
  }
}
//retrieve minigame beat song
void Song::setMinigameSong(std::string songFile) {
  std::ifstream i("../Rhythm_Charter/timingChart.json");
  nlohmann::json timingChart;
  i >> timingChart;
  //check if timing chart exists
  if(timingChart.at(songFile)) {
    if (!music.openFromFile(AUD_PATH_BASE + songFile))
      std::cout << "Could not load music." << std::endl;
    music.setVolume(40.0f); // Reduce music to 10%
  }
}

//set alternative music to play (non minigame states)
void Song::setMusic(std::string songFile) {
  if (!music.openFromFile(AUD_PATH_BASE + songFile))
    std::cout << "Could not load music." << std::endl;
  music.setVolume(40.0f); // Reduce music to 10%
}

//set a sound to be played for sound effects
void Song::setSound(std::string soundFile) {
  if (!music.openFromFile(AUD_PATH_BASE + soundFile))
    std::cout << "Could not load sound." << std::endl;
  sound.setBuffer(buffer);
  sound.setVolume(40.0f); // Reduce music to 10%
}

float Song::getACorrectTiming(int index)
{
  // Allows us to know we're at the end of the song
  if (index + 1 == correctTimings.size())
  {
    return 50000;
  }

  // Return the next beat
  return correctTimings.at(index);
}
