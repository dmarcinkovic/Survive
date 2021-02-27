#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/TexturedModel.h"
#include "engine/objects/Object3D.h"
#include "engine/camera/Camera.h"
#include "engine/light/Light.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"
#include "editor/editor/Editor.h"
#include "engine/events/EventHandler.h"
#include "engine/constant/Constants.h"
#include "engine/terrain/TerrainGenerator.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	Terrain terrain(TerrainGenerator::generateTerrain(loader, "res/heightmap.jpeg"), glm::vec3{-200, -10, -200},
					glm::vec3{400, 1, 400});
	terrain.addTextures("res/blendMap.png", {"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"});

	Renderer3D renderer(light);
	renderer.addTerrain(terrain);

	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));
	Entity sky(texturedModel, glm::vec3{}, glm::vec3{500});

	renderer.addSkyboxEntity(sky);

	TexturedModel dragonModel(ObjParser::loadObj("res/dragon.obj", loader), Loader::loadTexture("res/lamp.jpg"));
	Object3D dragon(dragonModel, glm::vec3{0, 0, -30});

	renderer.add3DObject(dragon);
	renderer.addShadow(dragon);

	Texture duDvTexture(Loader::loadTexture("res/waterDUDV.png"));
	Texture normalMap(Loader::loadTexture("res/normalMap.png"));
	WaterTile waterTile(loader.renderQuad(), 0, Constants::WATER_HEIGHT, -20, duDvTexture, normalMap);

	renderer.addWaterTile(waterTile);

	Editor editor(renderer.getRenderedTexture());
	EventHandler eventHandler(camera);
	eventHandler.registerListener(editor.isSceneWindowFocused());

	while (display.isRunning())
	{
		Display::clearWindow();

		Editor::newFrame();
		Editor::dock();
		editor.render();

		renderer.renderToFbo(camera);

		display.update();
	}

	return 0;
}
