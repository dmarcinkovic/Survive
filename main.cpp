#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"
#include "engine/terrain/TerrainGenerator.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1.0f, 1.0f, 1.0f});

	Renderer3D renderer(light);

	Terrain terrain(TerrainGenerator::generateTerrain(loader, "res/heightmap.jpeg"), glm::vec3{-200, -10, -200},
					glm::vec3{400, 1, 400});
	terrain.addTextures("res/blendMap.png", {"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"});
	renderer.addTerrain(terrain);

	auto textures = Loader::loadTextures({"res/lamp_bloom.png", "res/lamp_bloom_emissive.png"});

	TexturedModel texturedModel(ObjParser::loadObj("res/lamp_bloom.obj", loader),
								textures["res/lamp_bloom.png"]);
	Object3D lamp(texturedModel, glm::vec3{-5, -10, -40}, glm::vec3{0, -90, 0}, false, glm::vec3{0.1f, 0.1f, 0.1f});
	Object3D lamp2(texturedModel, glm::vec3{8, -10, -40}, glm::vec3{0, -90, 0}, false, glm::vec3{0.1f, 0.1f, 0.1f});

	renderer.add3DObject(lamp);
	renderer.add3DObject(lamp2);

	Texture lampBloom(textures["res/lamp_bloom_emissive.png"]);
	renderer.addBloom(lamp);
	renderer.addBloom(lamp2);

	lamp.addBloomEffect(lampBloom);
	lamp2.addBloomEffect(lampBloom);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(camera);

		display.update();
	}

	return 0;
}
