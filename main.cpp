#include "Font.h"
#include "Text.h"
#include "Renderer2D.h"
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

	constexpr int width = 1400;
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

	Text text("Text", font, glm::vec3{-0.5, -0.5, 0}, glm::vec3{1,0,0});
	text.loadTexture(loader);
	text.addBorder(0.9f, glm::vec3{0,1,0});
	text.centerText();

	Renderer2D renderer2D(loader);
	renderer2D.addText(text);

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
		renderer2D.render(registry);

		display.update();
	}

	return 0;
}
