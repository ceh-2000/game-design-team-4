#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

class Song
{
public:
    // Constructor
    Song(std::vector<std::string> songFilePaths, std::vector<std::string> soundFilePaths);

    // Destructor
    ~Song() {}

    // Getters, setters, and other short methods
    void play() { music.play(); }
    void pause() { music.pause(); }
    void stop() { music.stop(); }
    void playSound() { sound.play(); }
    void pauseSound() { sound.play(); }
    void stopSound() { sound.stop(); }
    sf::Sound::Status getSoundStatus() { return sound.getStatus(); }
    float getSongTime() { return sf::Time(music.getPlayingOffset()).asSeconds(); }
    std::vector<float> getAllTimings(){ return correctTimings; }

    // Methods with logic
    float getACorrectTiming(int index);
private:
    sf::Music music;
    sf::Sound sound;
    sf::SoundBuffer buffer;
    std::vector<float> correctTimings;
};
