#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main(int argc, char **argv)
{
  // Create main window
  sf::RenderWindow app(sf::VideoMode(800, 600, 32), "Quick Quisine", sf::Style::Titlebar | sf::Style::Close);

  Game game("../data/survive.wav");
  game.setCurrentSong("../data/survive.wav");

  // Set up variables that will allow us to get the elapsed time
  float deltaTime = 0.0f;
  sf::Clock clock;

  // Start main loop
  while (app.isOpen())
  {
    // Process events
    sf::Event Event;
    while (app.pollEvent(Event))
    {
      // Exit
      if (Event.type == sf::Event::Closed)
        app.close();
      if (Event.type == sf::Event::KeyPressed)
      {
        if (Event.key.code == sf::Keyboard::Space)
        {
          game.tapCheck(app);
        }
      }
    }

    // Get how much time has passed
    deltaTime = clock.restart().asSeconds();

    game.update(app, deltaTime);
  }

  // Done.
  return 0;
}
