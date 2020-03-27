
#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/shader/Shader.h"
#include "engine/texture/Texture.h"
#include "engine/renderer/Renderer2D.h"

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

    Shader shader("engine/shader/sources/VertexShader.glsl",
                  "engine/shader/sources/FragmentShader.glsl");

    Renderer2D renderer(shader);

    std::vector<Entity2D> entities;
    entities.emplace_back(Entity2D(texture));

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render(entities);

        display.update();
    }

    return 0;
}
