#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	Renderer3D renderer3D(light);

	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));
	Entity sky(texturedModel, glm::vec3{}, glm::vec3{500});

	renderer3D.addSkyboxEntity(sky);

	TexturedModel dragonModel(ObjParser::loadObj("res/dragon.obj", loader), Loader::loadTexture("res/lamp.jpg"));
	Object3D dragon(dragonModel, glm::vec3{-5, 0, -30});
	Object3D dragon2(dragonModel, glm::vec3{5, 0, -30});

	renderer3D.add3DObject(dragon);
	renderer3D.addShadow(dragon);
	renderer3D.add3DObject(dragon2);
	renderer3D.addShadow(dragon2);

	renderer3D.addOutlineToObject(dragon);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer3D.render(camera);

		display.update();
	}

	return 0;
}
