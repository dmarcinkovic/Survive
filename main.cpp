#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/Texture.h"
#include "engine/renderer/Renderer2D.h"
#include "engine/text/Font.h"
#include "engine/text/TextRenderer.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
    Renderer2D renderer(loader);

    Font font("res/candara.png", loader);
    font.loadFontFromFntFile("res/candara.fnt");

    Text text("D", font, glm::vec3{0, 0, 0}, glm::vec3{1, 0, 1}, 10.0);
    text.centerText();
    text.addBorder(0.5, glm::vec3{1, 0, 0});

    renderer.addText(text);
    text.setText("AB", loader);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
