#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/obj/ObjLoader.h"
#include "engine/objects/ObjectShader.h"
#include "engine/entity/Entity.h"
#include "engine/renderer/Renderer2DUtil.h"
#include "engine/math/Maths.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    Texture texture{ObjLoader::loadObj("res/house.obj", loader),
                    loader.loadTexture("res/house.png")};

    Entity entity2D{texture, glm::vec3{0, 0, 0}, 1};

    Camera camera{};

    ObjectShader shader{};
    shader.start();
    shader.loadProjectionMatrix(Maths::createProjectionMatrix(70, 0.1, 1000));
    ObjectShader::stop();

    float angle = 0.0f;
    while (display.isRunning())
    {
        Display::clearWindow();

        glEnable(GL_DEPTH_TEST);

        shader.start();
        Renderer2DUtil::prepareEntity(texture);

        shader.loadTransformationMatrix(Maths::createTransformationMatrix(
                glm::vec3{0, -3, -25}, 1, 1, 1, 0, angle));
        angle += 0.1f;
        shader.loadViewMatrix(Maths::createViewMatrix(camera));

        glDrawArrays(GL_TRIANGLES, 0, texture.vertexCount());

        Renderer2DUtil::finishRenderingEntity();
        ObjectShader::stop();

        display.update();
    }

    return 0;
}
