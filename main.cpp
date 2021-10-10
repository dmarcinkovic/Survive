#include "Editor.h"
#include "EventHandler.h"
#include "Loader.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"
#include "Display.h"
#include "entt.hpp"
#include "Components.h"

int main()
{
	using namespace Survive;

	constexpr int width = 1500;
	constexpr int height = 900;

	Display display(width, height, "Survive");
	Loader loader;

	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	entt::registry registry;
	Renderer renderer(light);

	Editor editor(renderer);

	auto rectangle = registry.create();
	registry.emplace<TagComponent>(rectangle, "rectangle");
	registry.emplace<Transform3DComponent>(rectangle, glm::vec3{-0.5f, 0, 0}, glm::vec3{0.25f, 0.25f, 1.0f});
	registry.emplace<Render2DComponent>(rectangle,
										TexturedModel(loader.renderQuad(), Loader::loadTexture("res/rectangle.png")));

	EventHandler eventHandler;

	while (display.isRunning())
	{
		Display::clearWindow();

		editor.handleKeyEvents(eventHandler);

		Editor::newFrame();
		Editor::dock();
		editor.render(registry, renderer, camera);

		renderer.renderToFbo(registry, camera);

		display.update();
	}

	return 0;
}
