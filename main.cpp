#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/components/TransformComponent.h"
#include "engine/components/RenderComponent.h"
#include "engine/sprites/SpritesRenderer.h"
#include "engine/sprites/SpriteUpdate.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	SpritesRenderer spritesRenderer;
	GuiRenderer guiRenderer;

	entt::registry registry;

	auto entity = registry.create();

	registry.emplace<RenderComponent>(entity,
									  TexturedModel(loader.renderQuad(), Loader::loadTexture("res/boy.png")));
	registry.emplace<TransformComponent>(entity, glm::vec3{0.5, 0.5, 0}, glm::vec3{0.5, 0.5, 0});
	registry.emplace<SpriteSheetComponent>(entity, 2, 4, 6, 0, 0, 0, 3);

	auto gui = registry.create();
	registry.emplace<RenderComponent>(gui, TexturedModel(loader.renderQuad(), Loader::loadTexture("res/circle.png")));
	registry.emplace<TransformComponent>(gui, glm::vec3{-0.5, 0.5, 0}, glm::vec3{0.5, 0.5, 0});

	while (display.isRunning())
	{
		Display::clearWindow();

		spritesRenderer.render(registry);
		guiRenderer.render(registry);

		SpriteUpdate::update(registry);

		display.update();
	}

	return 0;
}
