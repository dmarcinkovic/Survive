#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/components/TransformComponent.h"
#include "engine/components/RenderComponent.h"
#include "engine/sprites/SpritesRenderer.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	SpritesRenderer spritesRenderer;

	entt::registry registry;

	auto entity = registry.create();

	registry.emplace<RenderComponent>(entity,
									  TexturedModel(loader.renderQuad(), Loader::loadTexture("res/loading.png")));
	registry.emplace<TransformComponent>(entity, glm::vec3{0.5, 0.5, 0}, glm::vec3{0.5, 0.5, 0});
	registry.emplace<Sprite>(entity, 4, 4, 12);

	while (display.isRunning())
	{
		Display::clearWindow();

		spritesRenderer.render(registry);

		display.update();
	}

	return 0;
}
