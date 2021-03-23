#include "Song.h"

Song::Song(std::string filename)
{
  // Open music file and play music
  // We open instead of loading to use less memory
  if (!music.openFromFile(filename))
    std::cout << "Could not load music." << std::endl;
  music.setVolume(40.0f); // Reduce music to 10%

  // TODO: Read in the JSON file with correct timings here and set our variable
  // For now, we just have a dummy vector of timings

  correctTimings = {6.79, 8.62, 10.63, 12.65, 14.65, 16.59, 18.576, 22.52, 23.02, 23.56, 24.04, 24.54, 25.03, 25.53};
}

Song::~Song()
{
}

void Song::play()
{
  // music.setPlayingOffset(sf::seconds(60.f));
  music.play();
}

void Song::pause()
{
  music.pause();
}

void Song::stop()
{
  music.stop();
}

float Song::getSongTime()
{
  return sf::Time(music.getPlayingOffset()).asSeconds();
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