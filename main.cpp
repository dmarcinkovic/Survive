#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/TexturedModel.h"
#include "engine/entity/Entity.h"
#include "engine/sky/SkyRenderer.h"

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));

	Entity sky(texturedModel, glm::vec3{});
	SkyRenderer skyRenderer(sky);

	while (display.isRunning())
	{
		Display::clearWindow();

		skyRenderer.render(camera);

		display.update();
	}

	return 0;
}
