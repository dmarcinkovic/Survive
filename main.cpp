#include <iostream>
#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	Terrain terrain(loader.renderQuad(), glm::vec3{0, -10, -50,}, glm::vec3{100, 100, 1});
	terrain.addTextures("res/blendMap.png", {"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"});

	Renderer3D renderer3D(light);
	renderer3D.addTerrain(terrain);

	TexturedModel dragonModel(ObjParser::loadObj("res/dragon.obj", loader), Loader::loadTexture("res/lamp.jpg"));
	Object3D dragon(dragonModel, glm::vec3{0, -10, -30});

	renderer3D.add3DObject(dragon);
	renderer3D.addShadow(dragon);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer3D.render(camera);

		display.update();
	}

	return 0;
}
