#include "Font.h"
#include "Text.h"
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
#include "AnimationSystem.h"

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

	DaeParser daeParser;
	auto character = registry.create();
	registry.emplace<TagComponent>(character, "character");
	TexturedModel texturedModel(daeParser.loadDae("res/character.dae", loader),
								Loader::loadTexture("res/character.png"));
	registry.emplace<Render3DComponent>(character, texturedModel);
	registry.emplace<Transform3DComponent>(character, glm::vec3{5, -10, -30}, glm::vec3{1.0f}, glm::vec3{-90, 0, 0});
	registry.emplace<RigidBodyComponent>(character, false);
	registry.emplace<ShadowComponent>(character, true);

	auto[rootJoint, numberOfJoints] = daeParser.getJointData();
	registry.emplace<AnimationComponent>(character, rootJoint, numberOfJoints);

	auto dragon = registry.create();
	registry.emplace<TagComponent>(dragon, "dragon");
	registry.emplace<Render3DComponent>(dragon, TexturedModel(ObjParser::loadObj("res/dragon.obj", loader),
															  Loader::loadTexture("res/lamp.jpg")));
	registry.emplace<RigidBodyComponent>(dragon, false);
	registry.emplace<Transform3DComponent>(dragon, glm::vec3{-5, -10, -40});
	registry.emplace<ShadowComponent>(dragon, true);

	Font font("res/arial.png", loader);
	font.loadFontFromFntFile("res/arial.fnt");

	auto textEntity = registry.create();

	Text text("Text", font);
	text.centerText();
	text.loadTexture(loader);

	registry.emplace<TagComponent>(textEntity, "text");
	registry.emplace<TextComponent>(textEntity, text);
	registry.emplace<Transform3DComponent>(textEntity, glm::vec3{-0.5, -0.5, 0});
	registry.emplace<SpriteComponent>(textEntity, glm::vec4{1, 0, 0, 1});

	Animator animator(daeParser.getAnimation());
	EventHandler eventHandler;

	while (display.isRunning())
	{
		Display::clearWindow();

		editor.handleKeyEvents(eventHandler);

		animator.update(registry);
		AnimationSystem::update(registry);

		Editor::newFrame();
		Editor::dock();
		editor.render(registry, renderer, camera);

		renderer.renderToFbo(registry, camera);

		display.update();
	}

	return 0;
}
