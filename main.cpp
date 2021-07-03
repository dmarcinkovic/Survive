#include "Editor.h"
#include "Loader.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"
#include "Display.h"
#include "entt.hpp"
#include "SceneLoader.h"

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

	auto lamp = registry.create();
	registry.emplace<TagComponent>(lamp, "lamp");

	auto sky = registry.create();
	registry.emplace<TagComponent>(sky, "sky");
	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));
	registry.emplace<Render3DComponent>(sky, texturedModel);
	registry.emplace<Transform3DComponent>(sky, glm::vec3{}, glm::vec3{500});

	renderer.addSkyboxEntity(sky);
//	registry.emplace<ReflectionComponent>(dragon, texturedModel.getTexture(), 0.5f);
//	registry.emplace<RefractionComponent>(dragon, texturedModel.getTexture(), 2.0f, 0.5f);

	SceneLoader sceneLoader;
	sceneLoader.loadScene(registry, "file.txt");

	while (display.isRunning())
	{
		Display::clearWindow();

		Editor::newFrame();
		Editor::dock();
		editor.render(registry);

		renderer.renderToFbo(registry, camera);

		display.update();
	}

	return 0;
}
