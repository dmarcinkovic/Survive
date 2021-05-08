#include <iostream>
#include "Editor.h"
#include "EventHandler.h"
#include "Loader.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer3D.h"
#include "Display.h"
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
	Renderer3D renderer(light);

	Editor editor(renderer.getRenderedTexture());
	EventHandler eventHandler(camera);
	eventHandler.registerListener(editor.isSceneWindowFocused());

	auto dragon = registry.create();
	registry.emplace<TagComponent>(dragon, "dragon");

	auto lamp = registry.create();
	registry.emplace<TagComponent>(lamp, "lamp");

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
