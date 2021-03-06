#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/text/TextRenderer.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/components/Transform3DComponent.h"
#include "engine/animations/renderer/AnimationRenderer.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Light light(glm::vec3{100, 100, 100}, glm::vec3{1, 1, 1});
	AnimationRenderer animationRenderer(light);
	Camera camera;

	entt::registry registry;

	auto entity = registry.create();
	

	while (display.isRunning())
	{
		Display::clearWindow();

		animationRenderer.render(registry, camera);

		display.update();
	}

	return 0;
}
