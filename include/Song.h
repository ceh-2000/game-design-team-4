#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

class Song
{
public:
    // Constructor
    Song(std::vector<std::string> filePaths);

    // Getters, setters, and other short methods
    void play() { music.play(); }
    void pause() { music.pause(); }
    void stop() { music.stop(); }
    float getSongTime() { return sf::Time(music.getPlayingOffset()).asSeconds(); }
    std::vector<float> getAllTimings(){ return correctTimings; }

    // Methods with logic
    float getACorrectTiming(int index);
private:
    sf::Music music;
    std::vector<float> correctTimings;
};