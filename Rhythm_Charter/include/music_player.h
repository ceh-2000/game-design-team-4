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
	
public:
	Music_Player(std::string path);
	
	void play(){ music.play(); playState = true; }
	void pause(){ music.pause(); playState = false; }
	void stop(){ music.stop(); playState = false; }
	void changeTrack(std::string &filePath) { this->music.openFromFile(filePath); }
	
	bool isPlaying() { return playState; }

	void increaseVolume(int v) { this->music.setVolume( this->music.getVolume() + v ); this->volume = std::to_string(this->music.getVolume());}
	void decreaseVolume(int v) { this->music.setVolume( this->music.getVolume() - v ); this->volume = std::to_string(this->music.getVolume());}
	std::string getVolume() { return this->volume; }

	void incrementPos(float p) { this->music.setPlayingOffset( this->music.getPlayingOffset() + sf::seconds(p)); }
	void decrementPos(float p) { this->music.setPlayingOffset( sf::Time(this->music.getPlayingOffset() - sf::seconds(p))); }
	std::string getText() {return play_time;}

	float getPlayTime(){return music.getPlayingOffset().asSeconds();}
	void setPlayTime(float pos){this->music.setPlayingOffset(sf::seconds(pos));}
	float getDuration() { return music.getDuration().asSeconds();}

	float getRatio() { return this->music.getPlayingOffset().asSeconds()/this->music.getDuration().asSeconds(); }

	void updateText();
};
#endif