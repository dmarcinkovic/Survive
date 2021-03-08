#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/light/Light.h"
#include "engine/camera/Camera.h"
#include "engine/entity/Entity.h"
#include "engine/sky/SkyRenderer.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	TexturedModel texturedModel(loader.renderCube(), Loader::loadCubeMap(
			{"res/right.png", "res/left.png", "res/top.png", "res/bottom.png", "res/front.png", "res/back.png"}));

	Light light(glm::vec3{100, 100, 100}, glm::vec3{1, 1, 1});
	Camera camera;

	entt::registry registry;

	auto sky = registry.create();
	registry.emplace<RenderComponent>(sky, texturedModel);
	registry.emplace<Transform3DComponent>(sky, glm::vec3{}, glm::vec3{500});

	SkyRenderer renderer;
	renderer.addSkyEntity(sky);

	while (display.isRunning())
	{
		Display::clearWindow();

		renderer.render(registry, camera);

		display.update();
	}

	return 0;
}
