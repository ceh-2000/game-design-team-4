#include <iostream>
#include <vector>
#include <dirent.h>
#include <SFML/Graphics.hpp>
#include "Game.h"

using std::cout; using std::cin;
using std::endl; using std::vector;

int getAudioData(std::shared_ptr<Song> &song) {
	DIR *dir; struct dirent *diread;
	std::vector<std::string> songList;
	std::vector<std::string> soundList;
	const std::string path = "../data/music/";

	if ((dir = opendir("../data/music/")) != nullptr) {
			while ((diread = readdir(dir)) != nullptr) {
					cout << diread->d_name << endl;
					if (diread->d_name[0] != '.') {
						if (diread->d_name[0] == 'S')
							soundList.push_back(diread->d_name);
						else if (diread->d_name[0] == 'M' )
							songList.push_back(diread->d_name);
					}
					//files.push_back(diread->d_name);
			}
			closedir (dir);
	} else {
			perror ("opendir");
			return EXIT_FAILURE;
	}

	for (auto file : soundList) std::cout << file << "| ";
	std::cout << std::endl;
	for (auto file : songList) std::cout << file << "| ";
	std::cout << std::endl;
	song = std::make_shared<Song>(songList, soundList);

return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
	//Retrieve complete audio archive
	std::shared_ptr<Song> song;
	getAudioData(song);

	Game game = Game(song);

	// Set up variables that will allow us to get the elapsed time
	float deltaTime = 0.0f;
	sf::Clock clock;
	int hitCheckfreq = 0;

	// Start main loop
	while (game.getActive())
	{
		deltaTime = clock.restart().asSeconds();

		game.update(deltaTime);
	}
// Done.
return 0;
}
