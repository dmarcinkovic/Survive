#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"
#include "engine/mousePicking/MousePicking.h"

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;

	Camera camera{};
	Light light(glm::vec3{10, 10, 10}, glm::vec3{1, 1, 1});

	Renderer3D renderer(light);

	TexturedModel texturedModel(ObjParser::loadObj("res/lamp_bloom.obj", loader),
								Loader::loadTexture("res/lamp_bloom.png"));
	Object3D lamp(texturedModel, glm::vec3{-5, -10, -40}, glm::vec3{0,-90,0}, false, glm::vec3{0.1f, 0.1f, 0.1f});
	Object3D lamp2(texturedModel, glm::vec3{8, -10, -40}, glm::vec3{0, -90, 0}, false, glm::vec3{0.1f, 0.1f, 0.1f});

	renderer.add3DObject(lamp);
	renderer.add3DObject(lamp2);

	MousePicking mousePicking;

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(camera);

		display.update();
	}

	return 0;
}
