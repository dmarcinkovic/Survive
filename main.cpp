#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"
#include "engine/terrain/TerrainGenerator.h"
#include "engine/water/WaterRenderer.h"

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	Terrain terrain(TerrainGenerator::generateTerrain(loader, "res/heightmap.jpeg"), glm::vec3{-200, -10, -200},
					glm::vec3{400, 1, 400});
	terrain.addTextures("res/blendMap.png", {"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"});

	Renderer3D renderer3D(light);
	renderer3D.addTerrain(terrain);

	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));
	Entity sky(texturedModel, glm::vec3{}, glm::vec3{500});

	renderer3D.addSkyboxEntity(sky);

	TexturedModel dragonModel(ObjParser::loadObj("res/dragon.obj", loader), Loader::loadTexture("res/lamp.jpg"));
	Object3D dragon(dragonModel, glm::vec3{0, 0, -30});

	renderer3D.add3DObject(dragon);
	renderer3D.addShadow(dragon);

	WaterRenderer waterRenderer;

	Texture duDvTexture(Loader::loadTexture("res/waterDUDV.png"));
	Texture normalMap(Loader::loadTexture("res/normalMap.png"));
	WaterTile waterTile(loader.renderQuad(), 0, -6, -20, duDvTexture, normalMap);

	waterRenderer.addWaterTile(waterTile);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer3D.render(camera);

		waterRenderer.render(camera, light);

		display.update();
	}

	return 0;
}
