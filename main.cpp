#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/light/Light.h"
#include "engine/camera/Camera.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/terrain/TerrainGenerator.h"
#include "engine/parser/ObjParser.h"
#include "engine/sky/SkyRotateSystem.h"
#include "engine/constant/Constants.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});
	Renderer3D renderer(light);

	entt::registry registry;

	TexturedModel dragonModel(ObjParser::loadObj("res/dragon.obj", loader),
							  Loader::loadTexture("res/lamp.jpg"));

	auto dragon = registry.create();
	registry.emplace<RenderComponent>(dragon, dragonModel);
	registry.emplace<Transform3DComponent>(dragon, glm::vec3{0, -6, -30});
	registry.emplace<RigidBodyComponent>(dragon, false);
	registry.emplace<IdComponent>(dragon, 1);
	renderer.addShadow(registry, dragon);
	renderer.addOutlineToObject(registry, dragon);

	auto dragon2 = registry.create();
	registry.emplace<RenderComponent>(dragon2, dragonModel);
	registry.emplace<Transform3DComponent>(dragon2, glm::vec3{-10, -6, -30});
	registry.emplace<RigidBodyComponent>(dragon2, false);
	registry.emplace<IdComponent>(dragon2, 3);
	renderer.addShadow(registry, dragon2);

	auto lamp = registry.create();
	registry.emplace<RenderComponent>(lamp, TexturedModel(ObjParser::loadObj("res/lamp_bloom.obj", loader),
														  Loader::loadTexture("res/lamp_bloom.png")));
	registry.emplace<Transform3DComponent>(lamp, glm::vec3{10, -6, -40}, glm::vec3{0.05f});
	registry.emplace<RigidBodyComponent>(lamp, false);
	registry.emplace<IdComponent>(lamp, 2);
	registry.emplace<BloomComponent>(lamp, Loader::loadTexture("res/lamp_bloom_emissive.png"), 10.0f);
	renderer.addShadow(registry, lamp);

	auto water = registry.create();
	registry.emplace<RenderComponent>(water, TexturedModel(loader.renderQuad(), Texture(0)));
	registry.emplace<Transform3DComponent>(water, glm::vec3{0, Constants::WATER_HEIGHT, -20}, glm::vec3{200});
	registry.emplace<TexturedComponent>(water, Loader::loadAllTextures({"res/waterDUDV.png", "res/normalMap.png"}));
	registry.emplace<MoveComponent>(water, 0.03f);

	auto sky = registry.create();
	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));
	registry.emplace<RenderComponent>(sky, texturedModel);
	registry.emplace<Transform3DComponent>(sky, glm::vec3{}, glm::vec3{500});
	registry.emplace<MoveComponent>(sky, 1.0f, -90.0f);

	renderer.addSkyboxEntity(sky);

	auto terrain = registry.create();
	registry.emplace<RenderComponent>(terrain,
									  TexturedModel(TerrainGenerator::generateTerrain(loader, "res/heightmap.png"),
													Loader::loadTexture("res/blendMap.png")));

	registry.emplace<Transform3DComponent>(terrain, glm::vec3{-200, -10, -200}, glm::vec3{1, 1, 1});
	registry.emplace<TexturedComponent>(terrain, Loader::loadAllTextures(
			{"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"}));

	while (display.isRunning())
	{
		Display::clearWindow();

		SkyRotateSystem::rotateSky(registry, sky);

		renderer.render(registry, camera);

		display.update();
	}

	return 0;
}
