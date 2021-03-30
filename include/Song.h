#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

class Song
{
public:
    Song(std::vector<std::string> filePaths);

    void play() { music.play(); }
    void pause() { music.pause(); }
    void stop() { music.stop(); }
    float getSongTime() { return sf::Time(music.getPlayingOffset()).asSeconds(); }
    float getACorrectTiming(int index);

private:
    sf::Music music;
    std::vector<float> correctTimings;
};