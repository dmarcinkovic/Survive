#include <Box2D/Box2D.h>
#include <chrono>
#include <iostream>

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
	registry.emplace<Transform3DComponent>(rectangle, glm::vec3{0, 0.7f, 0}, glm::vec3{0.25f, 0.25f, 1.0f});
	registry.emplace<Render2DComponent>(rectangle,
										TexturedModel(loader.renderQuad(), Loader::loadTexture("res/rectangle.png")));

	auto *world = new b2World(b2Vec2(0.0f, -9.81f));

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	// TODO Set position from transform 3d when the user clicks play
	// TODO Find all entities that have this component and transform3d and set position
	bodyDef.position.Set(0, 0.7f * 10.0f);

	// TODO define bodyDef.angle from transform 3d component

	// TODO create the body/bodies when the user clicks on play button
	b2Body *body = world->CreateBody(&bodyDef);

	// TODO add this into circle, box, polygon collider
	// TODO when play is clicked, after creating body check if this component is presented and
	// TODO create fixture, it is not required to have fixture, this is only to enable object to collide
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.25f * 10.0f, 0.25f * 10.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;

	body->CreateFixture(&fixtureDef);

	auto ground = registry.create();
	registry.emplace<TagComponent>(ground, "ground");
	registry.emplace<Transform3DComponent>(ground, glm::vec3{-0.55f, -0.8f, 0}, glm::vec3{0.4f, 0.05f, 1.0f});
	registry.emplace<Render2DComponent>(ground,
										TexturedModel(loader.renderQuad(), Loader::loadTexture("res/dirt.png")));

	b2BodyDef bd;
	bd.type = b2_staticBody;
	bd.position.Set(-0.55f * 10.0f, -0.8f * 10.0f);

	b2Body *groundBody = world->CreateBody(&bd);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(0.4f * 10.0f, 0.05f * 10.0f);

	b2FixtureDef def;
	def.shape = &groundShape;
	def.density = 1.0f;
	def.friction = 0.3f;
	def.restitution = 0.5f;

	groundBody->CreateFixture(&def);

//	world->GetBodyList();

	EventHandler eventHandler;

	while (display.isRunning())
	{
		Display::clearWindow();

		editor.handleKeyEvents(eventHandler);

		Editor::newFrame();
		Editor::dock();
		editor.render(registry, renderer, camera);

		renderer.renderToFbo(registry, camera);

		b2Vec2 pos = body->GetPosition();
		float rotation = body->GetAngle();

		Transform3DComponent &transform = registry.get<Transform3DComponent>(rectangle);
		transform.position = glm::vec3{pos.x * 0.1f, pos.y * 0.1f, 1.0f};
		transform.rotation.z = glm::degrees(rotation);

		float frameRate = ImGui::GetIO().Framerate;
		world->Step(1.0f / frameRate, 5, 5);

		display.update();
	}

	delete world;

	return 0;
}
