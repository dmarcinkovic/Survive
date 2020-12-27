#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/TexturedModel.h"
#include "engine/entity/Entity.h"
#include "engine/sky/SkyRenderer.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"
#include "engine/outline/OutlineRenderer.h"

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	Loader loader;
	Camera camera;
	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));

	Entity sky(texturedModel, glm::vec3{});
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1, 1, 1});
	Renderer3D renderer(light);

	TexturedModel dragonModel(ObjParser::loadObj("res/dragon.obj", loader), Loader::loadTexture("res/lamp.jpg"));
	Object3D dragon(dragonModel, glm::vec3{0, -5, -30});
	dragon.m_Skybox = sky.m_Texture.getTexture();
	dragon.m_ReflectiveFactor = 0.3;

	renderer.add3DObject(dragon);
	renderer.addSkyboxEntity(sky);
	renderer.addOutlineToObject(dragon);

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(camera);

		display.update();
	}

	return 0;
}
