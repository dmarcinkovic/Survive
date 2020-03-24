
#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/shader/Shader.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    std::vector<float> vertices = {-0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5};
    std::vector<unsigned> indices = {0, 1, 2, 0, 2, 3};

    Loader loader;
    Model model = loader.loadToVao(vertices, indices, 2);

    Shader shader("engine/shader/VertexShader.glsl",
                  "engine/shader/FragmentShader.glsl");

    while (display.isRunning())
    {
        Display::clearWindow();

        glBindVertexArray(model.vao);
        glEnableVertexAttribArray(0);
        shader.start();

        glDrawElements(GL_TRIANGLES, model.vertexCount, GL_UNSIGNED_INT, nullptr);

        Shader::stop();
        glDisableVertexAttribArray(0);
        Loader::unbindVao();

        display.update();
    }

    return 0;
}
