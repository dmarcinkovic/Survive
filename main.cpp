
#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/shader/Shader.h"
#include "engine/texture/Texture.h"

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

    Shader shader("engine/shader/VertexShader.glsl",
                  "engine/shader/FragmentShader.glsl");

    while (display.isRunning())
    {
        Display::clearWindow();

        shader.start();
        texture.bindTexture();

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        Shader::stop();

        Texture::unbindTexture();
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
        Loader::unbindVao();

        display.update();
    }

    return 0;
}
