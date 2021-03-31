#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main(int argc, char **argv)
{
	std::vector<std::string> songList;
	songList.push_back("../data/music/Sixty_BPM.wav");

	std::shared_ptr<Song> song = std::make_shared<Song>(songList);
	std::shared_ptr<Game> game = std::make_shared<Game>(song);

	// Set up variables that will allow us to get the elapsed time
	float deltaTime = 0.0f;
	sf::Clock clock;
	int hitCheckfreq = 0;
	
	// Start main loop
	while (game->getActive())
	{
		deltaTime = clock.restart().asSeconds();

		game->update(deltaTime);
	}
// Done.
return 0;
}