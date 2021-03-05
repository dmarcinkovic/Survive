#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "ecs/entt.hpp"
#include "engine/text/Text.h"
#include "engine/text/TextRenderer.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");
	Loader loader;

	Font font("res/arial.png", loader);
	font.loadFontFromFntFile("res/arial.fnt");
	Text text("Some text", font, glm::vec3{}, glm::vec3{1, 0, 0}, 1);
	text.centerText();

	TextRenderer textRenderer;
	textRenderer.addText(text, loader);

	entt::registry registry;

	auto entity = registry.create();

	while (display.isRunning())
	{
		Display::clearWindow();

		textRenderer.renderText();

		display.update();
	}

	return 0;
}
