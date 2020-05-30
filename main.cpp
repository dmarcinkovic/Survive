#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/Texture.h"
#include "engine/renderer/Renderer2D.h"
#include "engine/ui/button/Button.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
    Renderer2D renderer(loader);

    Texture texture(renderer.getModel(), 1);
    Font font("res/candara.png", loader);
    font.loadFontFromFntFile("res/candara.fnt");

    Button button(texture, glm::vec3{0, 0.5, 0}, 0.4, 0.2,
                  glm::vec4{1, 0, 0, 0.6}, "Button1", font);
    Button button2(texture, glm::vec3{0, 0, 0}, 0.3, 0.1,
                   glm::vec4{0, 1, 0, 0.4}, "Button2", font);

    renderer.addButton(button);
    renderer.addButton(button2);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
