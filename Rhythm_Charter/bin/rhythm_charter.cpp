#include <SFML/Graphics.hpp>
#include "chart_view.h"

int main(int argc, char** argv)
{
	std::shared_ptr<Chart_Logic> chart_logic = std::make_shared<Chart_Logic>();
	std::shared_ptr<Chart_View> chart_view = std::make_shared<Chart_View>(chart_logic);

	// start main loop
	sf::Clock dtClock;  
	float dt = 0.0f;

	while(chart_logic->getActive())
	{
		dt = dtClock.restart().asSeconds();
		chart_view->update(dt);
	}
	// Done.
	return 0;
}