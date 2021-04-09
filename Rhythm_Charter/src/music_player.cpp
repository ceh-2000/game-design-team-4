#include "music_player.h"

Music_Player::Music_Player(std::string &path)
{
    this->music.openFromFile(path);
    this->music.setVolume(50);
    this->music.setLoop(true);
}

Music_Player::Music_Player(std::vector<std::string> &filePaths)
{
    this->music.openFromFile(filePaths.at(0));
    this->music.setVolume(50);
    this->music.setLoop(true);
    this->list = true;
}

void Music_Player::updateText()
{   
    this->times[0] = std::to_string(int(floor(this->music.getPlayingOffset().asSeconds()/60)));
    this->times[1] = std::to_string(int(this->music.getPlayingOffset().asSeconds())%60);
    this->times[2] = std::to_string(int(floor(this->music.getDuration().asSeconds()/60)));
    this->times[3] = std::to_string(int(this->music.getDuration().asSeconds())%60);

    for (int i = 0; i < 4; i++)
        if(times[i].length()==1)
            times[i] = "0" + times[i];
    
    this->play_time = this->times[0] + ":" + this->times[1] + " / " + this->times[2] + ":" + this->times[3];
}