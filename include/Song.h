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
    //Song methods
    void setMusic(std::string songFile);
    void setMinigameSong(std::string songFile);

    void playSong() { music.play(); }
    void pauseSong() { music.pause(); }
    void stopSong() { music.stop(); }
    float getSongTime() { return music.getPlayingOffset().asSeconds(); }

    //Sound methods
    void setSound(std::string soundFile);
    void playSound() { sound.play(); }
    void pauseSound() { sound.play(); }
    void stopSound() { sound.stop(); }
    sf::Sound::Status getSoundStatus() { return sound.getStatus(); }
    void setSoundPitch(float pitch) { sound.setPitch(pitch); }

    void setGameStateAudio(int state);
    std::vector<float> getAllTimings(){ return correctTimings; }

    // Methods with logic
    float getACorrectTiming(int index);

private:
    //NOTE: AUDIO FILES FORMATTED (M,S){1,2,3,4}_<audiofile_name>.<filetype>
    //(M,S) determines if either Sound (S) or Music (M)
    //{1,2,3,4} Determines which song files are for minigame beats
    //Default song files do not get file prefixes (M,S){1,2,3,4}_, they go in var basicSongs
    const std::vector<std::string> basicSongs = { "sixty_BPM.wav", "sixty_BPM.wav", "sixty_BPM.wav", "sixty_BPM.wav"}; //INSERT YOUR DEFAULT MINIGAME SONGS IN HERE
    std::vector<std::string> songFilePaths;
    std::vector<std::string> soundFilePaths;
    sf::Music music;
    sf::Sound sound;
    sf::SoundBuffer buffer;
    std::vector<float> correctTimings;
};
