#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"
#include "engine/gaussianBlur/BloomRenderer.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	Renderer3D renderer(light);

	TexturedModel texturedModel(ObjParser::loadObj("res/lamp_bloom.obj", loader),
								Loader::loadTexture("res/lamp_bloom.png"));
	Object3D lamp(texturedModel, glm::vec3{-5, -10, -40}, glm::vec3{0,-90,0}, false, glm::vec3{0.1f, 0.1f, 0.1f});
	Object3D lamp2(texturedModel, glm::vec3{8, -10, -40}, glm::vec3{0, -90, 0}, false, glm::vec3{0.1f, 0.1f, 0.1f});

	renderer.add3DObject(lamp);
	renderer.add3DObject(lamp2);

	Texture lampBloom(Loader::loadTexture("res/lamp_bloom_emissive.png"));
	BloomRenderer bloomRenderer(width / 8, height / 8);
	bloomRenderer.addObject(lamp);
	bloomRenderer.addObject(lamp2);

	lamp.addBloomEffect(lampBloom);
	lamp2.addBloomEffect(lampBloom);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(camera);
		bloomRenderer.render();

		display.update();
	}

	return 0;
}
