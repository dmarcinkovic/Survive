#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;

	while (display.isRunning())
	{
		Display::clearWindow();


		display.update();
	}

	return 0;
}
