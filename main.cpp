#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/obj/ObjLoader.h"
#include "engine/objects/ObjectShader.h"
#include "engine/entity/Entity2D.h"
#include "engine/renderer/RendererUtil.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    Model model = ObjLoader::loadObj("res/house.obj", loader);
    Texture texture{model, loader.loadTexture("res/house2.png")};

    Entity2D entity2D{texture, glm::vec3{0, 0, 0}, 1};

    ObjectShader shader{};

    while (display.isRunning())
    {
        Display::clearWindow();

        shader.start();
        RendererUtil::prepareEntity(texture);
        glDrawElements(GL_TRIANGLES, model.m_VertexCount, GL_UNSIGNED_INT, nullptr);
        RendererUtil::finishRenderingEntity();
        ObjectShader::stop();

        display.update();
    }

    return 0;
}
