#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/light/Light.h"
#include "engine/camera/Camera.h"
#include "engine/entity/Entity.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/terrain/TerrainGenerator.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Light light(glm::vec3{100, 100, 100}, glm::vec3{1, 1, 1});
	Camera camera;

	entt::registry registry;

	auto terrain = registry.create();
	registry.emplace<RenderComponent>(terrain,
									  TexturedModel(TerrainGenerator::generateTerrain(loader, "res/heightmap.jpeg"),
													Loader::loadTexture("res/blendMap.png")));

	registry.emplace<Transform3DComponent>(terrain, glm::vec3{-200, -10, -200}, glm::vec3{400, 1, 400});
	registry.emplace<TexturedComponent>(terrain, Loader::loadAllTextures(
			{"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"}));

	Renderer3D renderer(light);

	auto sky = registry.create();
	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));
	registry.emplace<RenderComponent>(sky, texturedModel);
	registry.emplace<Transform3DComponent>(sky, glm::vec3{}, glm::vec3{500});

	renderer.addSkyboxEntity(sky);

	Texture duDvTexture(Loader::loadTexture("res/waterDUDV.png"));
	Texture normalMap(Loader::loadTexture("res/normalMap.png"));
	WaterTile waterTile(loader.renderQuad(), 0, -6, -20, duDvTexture, normalMap);

	renderer.addWaterTile(waterTile);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(registry, camera);

		display.update();
	}

	return 0;
}
