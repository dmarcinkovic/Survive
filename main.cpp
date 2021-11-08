#include <reactphysics3d/reactphysics3d.h>

#include "Editor.h"
#include "EventHandler.h"
#include "DaeParser.h"
#include "Animator.h"
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
	camera.position = glm::vec3{0, 0, 8};
	
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	entt::registry registry;
	Renderer renderer(light);

	Editor editor(renderer);

	auto cube = registry.create();
	registry.emplace<Transform3DComponent>(cube, glm::vec3{0, 2, -10}, glm::vec3{1.0f}, glm::vec3{0, 30, 0});
	registry.emplace<RigidBodyComponent>(cube, false);
	registry.emplace<Render3DComponent>(cube, TexturedModel(ObjParser::loadObj("res/cube.obj", loader), Texture()));
	registry.emplace<SpriteComponent>(cube, glm::vec4{0.8f, 0.3f, 0.1f, 1.0f});

	auto ground = registry.create();
	registry.emplace<Transform3DComponent>(ground, glm::vec3{0, -2, -10}, glm::vec3{6, 0.5f, 8});
	registry.emplace<RigidBodyComponent>(ground, false);
	registry.emplace<Render3DComponent>(ground, TexturedModel(ObjParser::loadObj("res/cube.obj", loader), Texture()));
	registry.emplace<SpriteComponent>(ground, glm::vec4{0, 0.3f, 0.8f, 1.0f});

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
