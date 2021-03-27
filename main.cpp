#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"
#include "engine/terrain/TerrainGenerator.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	Light light(glm::vec3{10000, 10000, 10000}, glm::vec3{1.0f, 1.0f, 1.0f});

	Renderer3D renderer(light);

	Terrain terrain(TerrainGenerator::generateTerrain(loader, "res/heightmap.png"), glm::vec3{-200, -10, -200},
					glm::vec3{1, 1, 1});
	terrain.addTextures("res/blendMap.png", {"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"});
	renderer.addTerrain(terrain);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(camera);

		display.update();
	}

	return 0;
}
