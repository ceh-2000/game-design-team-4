#include "Song.h"
#include "json.h"
#include <fstream>

Song::Song(std::vector<std::string> songFilePaths, std::vector<std::string> soundFilePaths)
{
  // Open music file and play music
  // We open instead of loading to use less memory
  if (!music.openFromFile(songFilePaths.at(0)))
    std::cout << "Could not load music." << std::endl;
  music.setVolume(40.0f); // Reduce music to 10%

  // Open sound effects
  if (!buffer.loadFromFile(soundFilePaths.at(0)))
    std::cout << "Could not load sound." << std::endl;
  sound.setBuffer(buffer);
  sound.setVolume(40.0f); // Reduce music to 10%

  // Read the json and get the timing vector
  std::ifstream i("../Rhythm_Charter/timingChart.json");
  nlohmann::json timingChart;
  i >> timingChart;

  timingChart.at("test").get_to(correctTimings);

  //dummy vector of timings
  //correctTimings = {6.79, 8.62, 10.63, 12.65, 14.65, 16.59, 18.576, 22.52, 23.02, 23.56, 24.04, 24.54, 25.03, 25.53};
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
