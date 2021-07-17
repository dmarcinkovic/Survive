#include <ObjParser.h>
#include <iostream>
#include "EventHandler.h"
#include "Editor.h"
#include "Loader.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"
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
	Renderer renderer(light);

	Editor editor(renderer.getRenderedTexture());

	auto dragon = registry.create();
	registry.emplace<TagComponent>(dragon, "dragon");
	registry.emplace<Render3DComponent>(dragon, TexturedModel(Model(ObjParser::loadObj("res/dragon.obj", loader)),
															  Loader::loadTexture("res/lamp.jpg")));
	registry.emplace<RigidBodyComponent>(dragon, false);
	registry.emplace<Transform3DComponent>(dragon, glm::vec3{0, 0, -20});

	auto sky = registry.create();
	registry.emplace<TagComponent>(sky, "sky");
	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));
	registry.emplace<Render3DComponent>(sky, texturedModel);
	registry.emplace<Transform3DComponent>(sky, glm::vec3{}, glm::vec3{500});

	renderer.addSkyboxEntity(sky);
//	registry.emplace<ReflectionComponent>(dragon, 0.5f);
	registry.emplace<RefractionComponent>(dragon, 2.0f, 0.5f);

	EventHandler eventHandler;

	while (display.isRunning())
	{
		Display::clearWindow();

		editor.handleKeyEvents(eventHandler);

		Editor::newFrame();
		Editor::dock();
		editor.render(registry);

		renderer.renderToFbo(registry, camera);

		display.update();
	}

	return 0;
}
