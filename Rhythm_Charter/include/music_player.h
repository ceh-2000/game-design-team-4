#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <SFML/Audio.hpp>
#include <string>
#include <cmath>

class Music_Player
{
private:
	sf::Music music;
	std::string path;
	std::string play_time;
	std::string volume;
	std::vector<std::string> playlist;
	std::string times[4];

	bool playState = false;
	bool list = false;
	int counter = 0;
	
public:
	Music_Player(std::string &path);
	Music_Player(std::vector<std::string> &filePaths);
	
	void play(){ music.play(); playState = true; }
	void pause(){ music.pause(); playState = false; }
	void stop(){ music.stop(); playState = false; }
	void changeTrack(std::string &filePath) { music.openFromFile(filePath); }
	void nextTrack() { if(list && counter+1 > playlist.size()) counter++; music.openFromFile(playlist.at(counter)); };
	void previousTrack() { if(list && counter-1 < playlist.size()) counter--; music.openFromFile(playlist.at(counter)); };

	bool isPlaying() { return playState; }

	void increaseVolume(int v) { music.setVolume( music.getVolume() + v ); volume = std::to_string(music.getVolume());}
	void decreaseVolume(int v) { music.setVolume( music.getVolume() - v ); volume = std::to_string(music.getVolume());}
	std::string &getVolume() { return this->volume; }

	void incrementPos(float p);
	void decrementPos(float p);
	std::string &getText() { return play_time; }

	float getPlayTime(){return music.getPlayingOffset().asSeconds();}
	void setPlayTime(float pos){this->music.setPlayingOffset(sf::seconds(pos));}
	float getDuration() { return music.getDuration().asSeconds();}

	float getRatio() { return this->music.getPlayingOffset().asSeconds()/this->music.getDuration().asSeconds(); }

	void updateText();
};
#endif