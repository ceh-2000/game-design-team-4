#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

class Song
{
public:
    Song(std::string filename);
    ~Song();

    void play();
    void pause();
    void stop();
    float getSongTime();

private:
    sf::Music music;
};