#include "MinigameView.h"

MinigameView::MinigameView(std::shared_ptr<MinigameLogic> logic, std::shared_ptr<sf::RenderWindow> app) {
    this->logic = logic;
    this->app = app;

    if (!texture.loadFromFile("../data/art/SatsanaSheet.png")) {
        std::cout << "Could not load Satsana sprite sheet." << std::endl;
    }

    rectSourceSprite.left = 0;
    rectSourceSprite.top = 0;
    rectSourceSprite.width = 128;
    rectSourceSprite.height = 128;

    //load in the font for result text
    if (!font.loadFromFile("../data/fonts/orange_kid.ttf")) {
        std::cout << "Could not load orange_kid.ttf." << std::endl;
    }
}

/*
Redraw the current background in response to a hit
*/
void MinigameView::updateBackground(int backgroundColor) {
    switch (backgroundColor) {
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
Create a new sprite and add it to our canvas given a row in the sprite sheet,
a poisiton, and a size
*/
void MinigameView::drawSprite(int row, sf::Vector2f position, sf::Vector2f size) {
    // TODO: Write this method to draw an animation
}

void MinigameView::draw() {
    this->app->display();
}

void MinigameView::update(const float &deltaTime) {
    // Hit logic
    this->logic->regionCheck();
    updateBackground(this->logic->getBackgroundColor());

    // Post-hit logic
    this->logic->updatePostHit(deltaTime);
}