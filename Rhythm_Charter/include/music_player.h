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
	std::vector<std::string> playlist;

	bool playState = false;

	std::string times[4];
public:
	Music_Player(std::string path);
	
	void play(){ music.play(); playState = true;}
	void pause(){ music.pause(); playState = false;}
	void stop(){ music.stop(); playState = false;}
	
	bool isPlaying() { return playState; }

	void increaseVolume(int v) { this->music.setVolume( this->music.getVolume() + v ); }
	void decreaseVolume(int v) { this->music.setVolume( this->music.getVolume() - v ); }

	void incrementPos(float p) { this->music.setPlayingOffset( this->music.getPlayingOffset() + sf::seconds(p)); }
	void decrementPos(float p) { this->music.setPlayingOffset( sf::Time(this->music.getPlayingOffset() - sf::seconds(p))); }

	void updateText();
	std::string getText() {return play_time;}

	float getPlayTime(){return music.getPlayingOffset().asSeconds();}
	void setPlayTime(float pos){this->music.setPlayingOffset(sf::seconds(pos));}
	float getDuration() { return music.getDuration().asSeconds();}

	float getRatio() { return this->music.getPlayingOffset().asSeconds()/this->music.getDuration().asSeconds(); }
};

#endif