#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/TexturedModel.h"
#include "engine/camera/Camera.h"
#include "engine/light/Light.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"
#include "editor/editor/Editor.h"
#include "engine/events/EventHandler.h"
#include "engine/terrain/TerrainGenerator.h"

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

	auto terrain = registry.create();
	registry.emplace<RenderComponent>(terrain,
									  TexturedModel(TerrainGenerator::generateTerrain(loader, "res/heightmap.png"),
													Loader::loadTexture("res/blendMap.png")));

	registry.emplace<Transform3DComponent>(terrain, glm::vec3{-200, -10, -200}, glm::vec3{1, 1, 1});
	registry.emplace<TexturedComponent>(terrain, Loader::loadAllTextures(
			{"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"}));
	Renderer3D renderer(light);

	auto sky = registry.create();
	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));
	registry.emplace<RenderComponent>(sky, texturedModel);
	registry.emplace<Transform3DComponent>(sky, glm::vec3{}, glm::vec3{500});

	renderer.addSkyboxEntity(sky);

	auto dragon = registry.create();
	registry.emplace<RenderComponent>(dragon, TexturedModel(ObjParser::loadObj("res/dragon.obj", loader),
															Loader::loadTexture("res/lamp.jpg")));
	registry.emplace<Transform3DComponent>(dragon, glm::vec3{0, 0, -30});
	registry.emplace<RigidBodyComponent>(dragon, false);
	renderer.addShadow(registry, dragon);
//	renderer.addOutlineToObject(dragon);

	Editor editor(renderer.getRenderedTexture());
	EventHandler eventHandler(camera);
	eventHandler.registerListener(editor.isSceneWindowFocused());

	while (display.isRunning())
	{
		Display::clearWindow();

		Editor::newFrame();
		Editor::dock();
		editor.render();

		renderer.renderToFbo(registry, camera);

		display.update();
	}

	return 0;
}
