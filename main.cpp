#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/gui/GuiRenderer.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/RenderComponent.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	GuiRenderer guiRenderer;

	entt::registry registry;

	auto entity = registry.create();

	registry.emplace<RenderComponent>(entity,
									  TexturedModel(loader.renderQuad(), Loader::loadTexture("res/circle.png")));
	registry.emplace<TransformComponent>(entity, glm::vec3{0.5, 0.5, 0}, glm::vec3{0.5, 0.5, 0});

	while (display.isRunning())
	{
		Display::clearWindow();

		guiRenderer.render(registry);

		display.update();
	}

	return 0;
}
