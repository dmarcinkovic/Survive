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

int main()
{
	constexpr int width = 1200;
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
	Object3D dragon(dragonModel, glm::vec3{-5, -5, -30});
	dragon.m_Skybox = sky.m_Texture.getTexture();
	dragon.m_ReflectiveFactor = 0.6;

	Object3D dragon2(dragonModel, glm::vec3{5, -5, -30});
	dragon2.m_Skybox = sky.m_Texture.getTexture();
	dragon2.m_ReflectiveFactor = 0.4;

	renderer.add3DObject(dragon);
	renderer.add3DObject(dragon2);
	renderer.addSkyboxEntity(sky);
	renderer.addShadow(dragon);
	renderer.addShadow(dragon2);

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
