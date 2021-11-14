#include "Application.h"

int main()
{
	constexpr int width = 1500;
	constexpr int height = 900;

<<<<<<< HEAD
	Survive::Application application(width, height, "Survive");
=======
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});
	Renderer3D renderer(light);

	entt::registry registry;

	auto dragon = registry.create();
	registry.emplace<RenderComponent>(dragon, TexturedModel(ObjParser::loadObj("assets/models/dragon.obj", loader),
															Loader::loadTexture("assets/textures/lamp.jpg")));
	registry.emplace<Transform3DComponent>(dragon, glm::vec3{-5, -5, -30});
	registry.emplace<RigidBodyComponent>(dragon, false);

	auto character = registry.create();
	DaeParser daeParser;
	TexturedModel texturedModel(daeParser.loadDae("assets/models/character.xml", loader),
								Loader::loadTexture("assets/textures/character.png"));
	registry.emplace<RenderComponent>(character, texturedModel);
	registry.emplace<Transform3DComponent>(character, glm::vec3{5, -10, -40}, glm::vec3{1.0f}, glm::vec3{-90, 0, 0});
	registry.emplace<RigidBodyComponent>(character, false);

	auto[rootJoint, numberOfJoints] = daeParser.getJointData();
	registry.emplace<AnimationComponent>(character, rootJoint, numberOfJoints);
	Animator animator(daeParser.getAnimation());

	auto terrain = registry.create();
	registry.emplace<RenderComponent>(terrain,
									  TexturedModel(TerrainGenerator::generateTerrain(loader,
																					  "assets/textures/heightmap.png"),
													Loader::loadTexture("assets/textures/blendMap.png")));

	registry.emplace<Transform3DComponent>(terrain, glm::vec3{-200, -10, -200}, glm::vec3{1, 1, 1});
	registry.emplace<TexturedComponent>(terrain, Loader::loadAllTextures(
			{"assets/textures/dirt.png", "assets/textures/grass.jpeg", "assets/textures/rock.png",
			 "assets/textures/flowers.png"}));

	renderer.addShadow(registry, character);

	while (display.isRunning())
	{
		Display::clearWindow();

		animator.update(registry);
		renderer.render(registry, camera);

		display.update();
	}
>>>>>>> master

	application.run();

	return 0;
}
