#include "Song.h"

Song::Song(std::string filename){
  // Open music file and play music 
  // We open instead of loading to use less memory
  if (!music.openFromFile(filename)) 
      std::cout << "Could not load music." << std::endl;
  music.setVolume(40.0f); // Reduce music to 10%
}

Song::~Song(){

}

void Song::play(){
  // music.setPlayingOffset(sf::seconds(60.f));
  music.play();
}

void Song::pause(){
  music.pause();
}

void Song::stop(){
  music.stop();
}

float Song::getSongTime(){
  return sf::Time(music.getPlayingOffset()).asSeconds();
}