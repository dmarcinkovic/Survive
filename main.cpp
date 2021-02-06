#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer3D.h"

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;

	while (display.isRunning())
	{
		Display::clearWindow();

		display.update();
	}

	return 0;
}
