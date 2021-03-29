#include <SFML/Graphics.hpp>
#include "chart_view.h"

int main(int argc, char** argv)
{
	std::shared_ptr<Chart_Logic> chart_logic = std::make_shared<Chart_Logic>();
	std::shared_ptr<Chart_View> chart_view = std::make_shared<Chart_View>(chart_logic);

	// start main loop
	while(chart_logic->getActive())
	{
		chart_view->update();
		sf::sleep(sf::milliseconds(16));
	}
	// Done.
	return 0;
}