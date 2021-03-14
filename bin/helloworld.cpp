#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main(int argc, char** argv)
{
  // Create main window
  sf::RenderWindow app(sf::VideoMode(800,600,32), "Quick Quisine", sf::Style::Titlebar | sf::Style::Close);
  sf::Music music;

  // Open music file and play music 
  // We open instead of loading to use less memory
  if (!music.openFromFile("../data/ChillingMusic.wav")) 
      std::cout << "Could not load music." << std::endl;
  music.play();

  // Start main loop
  while(app.isOpen())
  {
    // Process events
    sf::Event Event;
    while(app.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        app.close();
    }

    // Clear screen and fill with blue
    app.clear(sf::Color::Blue);

    // Display
    app.display();
  }

  // Done.
  return 0;
}
