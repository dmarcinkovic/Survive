
#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/shader/Shader.h"
#include "engine/texture/Texture.h"
#include "engine/gui/GuiRenderer.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    std::vector<float> vertices = {-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5};
    std::vector<unsigned> indices = {0, 1, 3, 3, 1, 2};
    std::vector<float> textureCoordinates = {0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0};

    Loader loader;
    Texture texture(loader.loadToVao(vertices, indices, textureCoordinates, 2),
                    loader.loadTexture("res/texture.jpg"));

    GuiRenderer renderer;
    renderer.addEntity(Entity2D(texture, glm::vec3{-0.5, 0.5,0.0}, 0.3));
    renderer.addEntity(Entity2D(texture, glm::vec3{0.5, 0.5,0.0}, 0.3));

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
