#include "Game.h"

Game::Game(std::shared_ptr<Song> song)
{
	this->song = song;
	song->play();
	this->elapsedDuration = this->duration;

	// load sprite sheet for Satsana
	if(!texture.loadFromFile("../data/art/SatsanaSheet.png")){
		std::cout << "Could not load Satsana sprite sheet." << std::endl;
	}
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	rectSourceSprite.width = 128;
	rectSourceSprite.height = 128;

	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
	sprite.setTextureRect(rectSourceSprite);

	//load in the font for result text
	if(!font.loadFromFile("../data/fonts/orange_kid.ttf")){
		std::cout << "Could not load orange_kid.ttf." << std::endl;
	}
	resultText.setFont(font);
	resultText.setString("");
	resultText.setCharacterSize(24);
	resultText.setFillColor(sf::Color::Black);
	resultText.setPosition(130, 40);

	Animation* Satsana = new Animation(animate, elapsedDuration, 3, 0.75f, false, resultText, sprite, rectSourceSprite);
}

/*
Gets the previous hit given a song time
*/
float Game::determinePrevTap(float songTime)
{
	if(tapNum == 0){
		return song->getACorrectTiming(tapNum);
	}
	return song->getACorrectTiming(tapNum-1);
}

/*
Gets the next hit given a song time
*/
float Game::determineNextTap(float songTime)
{
	float nextTap = song->getACorrectTiming(tapNum);
	if(std::abs(nextTap - 50000) < 0.01){
		return nextTap;
	}
	while (songTime > nextTap)
	{
		tapNum = tapNum + 1;
		nextTap = song->getACorrectTiming(tapNum);
	}
	return nextTap;
}

/*
Check whether the player did not tap in previous action region
*/
void Game::regionCheck()
{
	float curSongTime = song->getSongTime();
	float nextTap = determineNextTap(curSongTime);
	float prevTap = determinePrevTap(curSongTime);

	// Kick-off an animation to show that the user missed because they never hit
	if(!isHit && std::abs(curSongTime - nextTap) > actRegion && std::abs(curSongTime - prevTap) > actRegion){
		std::cout << "No tap in action region" << std::endl;
		std::cout << "Miss!" << std::endl;
		backgroundColor = 3;
		isHit = true;
		animate = true;
		resultText.setString("Try Again!");
		resetHitYet = false;
	}
	else if((std::abs(curSongTime - nextTap) > actRegion && std::abs(curSongTime - prevTap) > actRegion)){
		resetHitYet = false;
	}
	// Reset once we reenter an active region
	else if(resetHitYet == false && std::abs(curSongTime - nextTap) < actRegion){
		isHit = false;
		resetHitYet = true;
	}
}

void Game::tapCheck()
{
	  float curSongTime = song->getSongTime();
	  float nextTap = determineNextTap(curSongTime);
	  float prevTap = determinePrevTap(curSongTime);

	  std::cout << "current to nextTap: " << std::abs(curSongTime - nextTap) << std::endl;
	  std::cout << "current to prevTap: " << std::abs(curSongTime - prevTap) << std::endl;

	  //current song time not in any tap action regions
	  if((std::abs(curSongTime - nextTap) > actRegion && std::abs(curSongTime - prevTap) > actRegion))
	  {
		  isHit = false;
		  backgroundColor = 0;
	  }

	  //current song time hit in success range
	  else if (std::abs(curSongTime - nextTap) < winRegion || std::abs(curSongTime - prevTap) < winRegion)
	  {
		  std::cout << "Hit!" << std::endl;
		  backgroundColor = 1;
		  isHit = true;
		  animate = true;
		  resultText.setString("Perfect!");
	  }
	  //current song time hit in almost range
	  else if (std::abs(curSongTime - nextTap) > winRegion && std::abs(curSongTime - prevTap) < almostRegion
			  || std::abs(curSongTime - nextTap) < winRegion && std::abs(curSongTime - prevTap) > almostRegion)
	  {
		  std::cout << "Almost!" << std::endl;
		  backgroundColor = 2;
		  isHit = true;
		  animate = true;
		  resultText.setString("Almost!");
	  }
	  //current song time hit in fail range
	  else
	  {
		  std::cout << "Miss!" << std::endl;
		  backgroundColor = 3;
		  isHit = true;
		  animate = true;
		  resultText.setString("Try Again!");
	  }
}

void Game::checkEvent()
{
	// Process events
	sf::Event event;
	while (app->pollEvent(event))
	{	
		switch(event.type)
		{
			case sf::Event::Closed: isActive = false; break;  // Exit
			case sf::Event::KeyPressed:
			switch(event.key.code)
			{
				case sf::Keyboard::Space: tapCheck(); break;
				default: break;
			}
			default: break;
	  }
	}
}

void Game::update(const float& deltaTime)
{
	regionCheck();
	checkEvent();

	// TODO: Extract all view logic to a view class

	// Animation logic
	// if(animate){
	// 	this->elapsedDuration += deltaTime;

	// 	while(this->elapsedDuration > this->duration){
	// 		this->elapsedDuration -= this->duration;

	// 		// cycle through 6 frames of talking
	// 		if(rectSourceSprite.left == 256){
	// 			rectSourceSprite.left = 0;
	// 		}
	// 		else{
	// 			rectSourceSprite.left += 128;
	// 		}
	// 		counter++;
	// 		if(counter == 6){
	// 			animate = false;
	// 			backgroundColor = 0;
	// 			counter = 0;
	// 			resultText.setString("");
	// 	   }
	// 	}
	// 	sprite.setTextureRect(rectSourceSprite);
	// }

	// Draw background and animation
	switch(this->backgroundColor)
	{
		case 0: this->app->clear(sf::Color::Blue); break; //blue
		case 1: this->app->clear(sf::Color::Green); break; //green	
		case 2: this->app->clear(sf::Color::Yellow); break; // yellow
		case 3: this->app->clear(sf::Color::Red); break; //red
	}
	//Upcoming changes?
	//if(animate)
	   Satsana->animateSprite(deltaTime, app);

	//this->app->draw(resultText);
	//this->app->draw(sprite);

	// Display
	this->app->display();
}