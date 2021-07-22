#include "ObjParser.h"
#include "EventHandler.h"
#include "Editor.h"
#include "Loader.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"
#include "Display.h"
#include "TerrainGenerator.h"
#include "entt.hpp"

int main()
{
	using namespace Survive;

	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	entt::registry registry;
	Renderer renderer(light);

	Editor editor(renderer.getRenderedTexture());

	auto dragon = registry.create();
	registry.emplace<TagComponent>(dragon, "dragon");

	Render3DComponent renderComponent(TexturedModel(Model(ObjParser::loadObj(
	"res/dragon.obj", loader)), Loader::loadTexture("res/lamp.jpg")));

	renderComponent.textureName = "res/lamp.jpg";
	renderComponent.modelName = "res/dragon.obj";
	registry.emplace<Render3DComponent>(dragon, renderComponent);
	registry.emplace<RigidBodyComponent>(dragon, false);
	registry.emplace<Transform3DComponent>(dragon, glm::vec3{0, -5, -40});
	registry.emplace<ShadowComponent>(dragon, true);

	auto terrain = registry.create();
	registry.emplace<TagComponent>(terrain, "terrain");
	registry.emplace<Render3DComponent>(terrain,
									  TexturedModel(TerrainGenerator::generateTerrain(loader, "res/heightmap.png"),
													Loader::loadTexture("res/blendMap.png")));

	registry.emplace<Transform3DComponent>(terrain, glm::vec3{-200, -10, -200}, glm::vec3{1, 1, 1});
	registry.emplace<TexturedComponent>(terrain, Loader::loadAllTextures(
			{"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"}));

	EventHandler eventHandler;

	while (display.isRunning())
	{
		Display::clearWindow();

		editor.handleKeyEvents(eventHandler);

		Editor::newFrame();
		Editor::dock();
		editor.render(registry, renderer);

		renderer.renderToFbo(registry, camera);
		camera.recalculateProjectionMatrix(Survive::Editor::getSceneWidth(), Survive::Editor::getSceneHeight());

		display.update();
	}

	return 0;
}
