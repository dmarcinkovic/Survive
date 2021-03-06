#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/light/Light.h"
#include "engine/camera/Camera.h"
#include "engine/terrain/Terrain.h"
#include "engine/terrain/TerrainGenerator.h"
#include "engine/terrain/TerrainRenderer.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Light light(glm::vec3{100, 100, 100}, glm::vec3{1, 1, 1});

	Camera camera;

	entt::registry registry;

	auto entity = registry.create();

	TerrainRenderer terrainRenderer;

	registry.emplace<Transform3DComponent>(entity, glm::vec3{-200, -10, -200}, glm::vec3{400, 1, 400});
	registry.emplace<RenderComponent>(entity,
									  TexturedModel(TerrainGenerator::generateTerrain(loader, "res/heightmap.jpeg"),
													Loader::loadTexture("res/blendMap.png")));
	registry.emplace<TexturedComponent>(entity, Loader::loadAllTextures({"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"}));

	while (display.isRunning())
	{
		Display::clearWindow();

		terrainRenderer.render(registry, camera, light, 0);

		display.update();
	}

	return 0;
}
