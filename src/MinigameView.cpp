#include "MinigameView.h"

MinigameView::MinigameView()
{
    // TODO: Pass in a shared pointer for app

    if (!texture.loadFromFile("../data/art/SatsanaSheet.png"))
    {
        std::cout << "Could not load Satsana sprite sheet." << std::endl;
    }

    rectSourceSprite.left = 0;
    rectSourceSprite.top = 0;
    rectSourceSprite.width = 128;
    rectSourceSprite.height = 128;

    //load in the font for result text
    if (!font.loadFromFile("../data/fonts/orange_kid.ttf"))
    {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }
}

/*
Redraw the current background in response to a hit
*/
MinigameView::updateBackground()
{
    switch (backgroundColor)
    {
    case 0:
        app->clear(sf::Color::Blue);
        break; //blue
    case 1:
        app->clear(sf::Color::Green);
        break; //green
    case 2:
        app->clear(sf::Color::Yellow);
        break; // yellow
    case 3:
        app->clear(sf::Color::Red);
        break; //red
    }
}

/*
Redraw all of our current beat boxes
*/
MinigameView::updateBeatBoxes(const std::vector<BeatBoxLogic>& beatBoxes){
    for (BeatBoxLogic beatBox : beatBoxes)
	{
		sf::RectangleShape box;
		box.setSize(sf::Vector2f(50, 50));
		box.setFillColor(sf::Color::Magenta);
		box.setPosition(beatBox.getCurPos());
		app->draw(box);
	}
}

/*
Create a new sprite and add it to our canvas given a row in the sprite sheet,
a poisiton, and a size
*/
MinigameView::drawSprite(int row, sf::Vector2f position, sf::Vector2f size){
    // TODO: Write this method to draw an animation
}

MinigameView::draw(){
    this->app->display();
}
