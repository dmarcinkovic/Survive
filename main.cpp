#include "ObjParser.h"
#include "EventHandler.h"
#include "Editor.h"
#include "TerrainGenerator.h"
#include "DaeParser.h"
#include "Animator.h"
#include "Loader.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"
#include "Display.h"
#include "TerrainGenerator.h"
#include "entt.hpp"
#include "Components.h"

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

	auto terrain = registry.create();
	registry.emplace<TagComponent>(terrain, "terrain");
	registry.emplace<Render3DComponent>(terrain,
									  TexturedModel(TerrainGenerator::generateTerrain(loader, "res/heightmap.png"),
													Loader::loadTexture("res/blendMap.png")));
	registry.emplace<Transform3DComponent>(terrain, glm::vec3{-200, -10, -200}, glm::vec3{1, 1, 1});
	registry.emplace<TexturedComponent>(terrain, Loader::loadAllTextures(
			{"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"}));

	auto character = registry.create();
	DaeParser daeParser;
	TexturedModel texturedModel(daeParser.loadDae("res/character.xml", loader),
								Loader::loadTexture("res/character.png"));
	registry.emplace<Render3DComponent>(character, texturedModel);
	registry.emplace<Transform3DComponent>(character, glm::vec3{0, -10, -40}, glm::vec3{1.0f}, glm::vec3{-90, 0, 0});
	registry.emplace<RigidBodyComponent>(character, false);
	
	auto[rootJoint, numberOfJoints] = daeParser.getJointData();
	registry.emplace<AnimationComponent>(character, rootJoint, numberOfJoints);
	Animator animator(daeParser.getAnimation());

	EventHandler eventHandler;

	while (display.isRunning())
	{
		Display::clearWindow();

		editor.handleKeyEvents(eventHandler);
		animator.update(registry);

		Editor::newFrame();
		Editor::dock();
		editor.render(registry, renderer);
		renderer.renderToFbo(registry, camera);

		camera.recalculateProjectionMatrix(Survive::Editor::getSceneWidth(), Survive::Editor::getSceneHeight());

		display.update();
	}

	return 0;
}
