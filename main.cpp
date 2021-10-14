#include <Box2D/Box2D.h>

#include "PhysicSystem.h"
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
	auto *world = new b2World(b2Vec2(0.0f, -9.81f));

	auto rectangle = registry.create();
	registry.emplace<TagComponent>(rectangle, "rectangle");
	registry.emplace<Transform3DComponent>(rectangle, glm::vec3{0, 0.7f, 0}, glm::vec3{0.25f, 0.25f, 1.0f});
	registry.emplace<Render2DComponent>(rectangle,
										TexturedModel(loader.renderQuad(), Loader::loadTexture("res/rectangle.png")));
	registry.emplace<RigidBody2DComponent>(rectangle, b2_dynamicBody);
	registry.emplace<BoxCollider2DComponent>(rectangle, 0.25f * 10.0f, 0.25f * 10.0f, 1.0f, 0.3f, 0.5f);

	auto ground = registry.create();
	registry.emplace<TagComponent>(ground, "ground");
	Transform3DComponent groundPos(glm::vec3{-0.55f, -0.8f, 0}, glm::vec3{0.4f, 0.05f, 1.0f});
	registry.emplace<Transform3DComponent>(ground, groundPos);
	registry.emplace<Render2DComponent>(ground,
										TexturedModel(loader.renderQuad(), Loader::loadTexture("res/dirt.png")));
	registry.emplace<RigidBody2DComponent>(ground, b2_staticBody);
	registry.emplace<BoxCollider2DComponent>(ground, 0.4f * 10.0f, 0.05f * 10.0f, 1.0f, 0.3f, 0.5f);

	PhysicSystem::init(registry, world);

	EventHandler eventHandler;

	while (display.isRunning())
	{
		Display::clearWindow();

		editor.handleKeyEvents(eventHandler);

		Editor::newFrame();
		Editor::dock();
		editor.render(registry, renderer, camera);

		renderer.renderEditor(registry, camera);

		PhysicSystem::update(registry);

		float frameRate = ImGui::GetIO().Framerate;
		world->Step(1.0f / frameRate, 5, 5);

		display.update();
	}

	delete world;

	return 0;
}
