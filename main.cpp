#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/light/Light.h"
#include "engine/camera/Camera.h"
#include "engine/terrain/Terrain.h"
#include "engine/terrain/TerrainGenerator.h"
#include "engine/terrain/TerrainRenderer.h"
#include "engine/fbo/FrameBuffer.h"
#include "engine/shadowMapping/ShadowRenderer.h"
#include "engine/constant/Constants.h"
#include "engine/parser/ObjParser.h"
#include "engine/objects/ObjectRenderer.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Light light(glm::vec3{100, 100, 100}, glm::vec3{1, 1, 1});
	Camera camera;
	ObjectRenderer objectRenderer(light);

	entt::registry registry;

	auto terrain = registry.create();

	TerrainRenderer terrainRenderer;

	registry.emplace<Transform3DComponent>(terrain, glm::vec3{-200, -10, -200}, glm::vec3{400, 1, 400});
	registry.emplace<RenderComponent>(terrain,
									  TexturedModel(TerrainGenerator::generateTerrain(loader, "res/heightmap.jpeg"),
													Loader::loadTexture("res/blendMap.png")));
	registry.emplace<TexturedComponent>(terrain, Loader::loadAllTextures(
			{"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"}));

	auto dragon = registry.create();
	registry.emplace<RenderComponent>(dragon, TexturedModel(ObjParser::loadObj("res/dragon.obj", loader),
															Loader::loadTexture("res/lamp.jpg")));
	registry.emplace<Transform3DComponent>(dragon, glm::vec3{0, 0, -30});
	registry.emplace<RigidBodyComponent>(dragon, false);

	FrameBuffer frameBuffer;
	GLuint shadowMap = frameBuffer.attachToDepthBufferTexture(Constants::SHADOW_WIDTH, Constants::SHADOW_HEIGHT);

	ShadowRenderer shadowRenderer;
	shadowRenderer.add3DObject(registry, dragon);

	while (display.isRunning())
	{
		Display::clearWindow();

		frameBuffer.renderToFrameBuffer(registry, shadowRenderer, camera, light, Constants::SHADOW_WIDTH,
										Constants::SHADOW_HEIGHT);
		terrainRenderer.render(registry, camera, light, shadowMap);
		objectRenderer.render(registry, camera, shadowMap);

		display.update();
	}

	return 0;
}
