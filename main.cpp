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
	TexturedModel skyModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));

	Entity sky(skyModel, glm::vec3{}, glm::vec3{500});
	Light light(glm::vec3{100, 100, 100}, glm::vec3{1, 1, 1});
	Renderer3D renderer(light);
	renderer.addSkyboxEntity(sky);

	TexturedModel texturedModel(ObjParser::loadObj("res/lamp_bloom.obj", loader),
								Loader::loadTexture("res/lamp_bloom.png"));
	Object3D lamp(texturedModel, glm::vec3{-5, -10, -40}, glm::vec3{0, -90, 0}, false, glm::vec3{0.1f, 0.1f, 0.1f});
	Object3D lamp2(texturedModel, glm::vec3{8, -10, -40}, glm::vec3{0, -90, 0}, false, glm::vec3{0.1f, 0.1f, 0.1f});

	renderer.add3DObject(lamp);
	renderer.add3DObject(lamp2);

	Texture lampBloom(Loader::loadTexture("res/lamp_bloom_emissive.png"));
	renderer.addBloom(lamp);
	renderer.addBloom(lamp2);

	lamp.addBloomEffect(lampBloom);
	lamp2.addBloomEffect(lampBloom);

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
