#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/light/Light.h"
#include "engine/camera/Camera.h"
#include "engine/terrain/TerrainGenerator.h"
#include "engine/parser/ObjParser.h"
#include "engine/renderer/Renderer3D.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Light light(glm::vec3{100, 100, 100}, glm::vec3{1, 1, 1});
	Camera camera;

	Renderer3D renderer(light);

	entt::registry registry;

	auto terrain = registry.create();

	registry.emplace<Transform3DComponent>(terrain, glm::vec3{-200, -10, -200}, glm::vec3{400, 1, 400});
	registry.emplace<RenderComponent>(terrain,
									  TexturedModel(TerrainGenerator::generateTerrain(loader, "res/heightmap.jpeg"),
													Loader::loadTexture("res/blendMap.png")));
	registry.emplace<TexturedComponent>(terrain, Loader::loadAllTextures(
			{"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"}));

	auto dragon = registry.create();
	registry.emplace<RenderComponent>(dragon, TexturedModel(ObjParser::loadObj("res/dragon.obj", loader),
															Loader::loadTexture("res/lamp.jpg")));
	registry.emplace<Transform3DComponent>(dragon, glm::vec3{0, 0, -30});
	registry.emplace<RigidBodyComponent>(dragon, false);
	registry.emplace<OutlineComponent>(dragon, true);

	renderer.addShadow(registry, dragon);

	OutlineRenderer outlineRenderer;
	outlineRenderer.add3DObject(registry, dragon);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(registry, camera);
		outlineRenderer.render(registry, camera);

		display.update();
	}

	return 0;
}
