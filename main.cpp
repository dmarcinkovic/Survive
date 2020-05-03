#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/Texture.h"
#include "engine/renderer/Renderer2D.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
    Renderer2D renderer(loader);

    Texture texture(renderer.getModel(), 0);
    Button button(texture, glm::vec3{0, 0, 0}, 0.5, 0.5,
                  glm::vec4{1, 0, 0, 0.7});

    renderer.addButton(button);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
