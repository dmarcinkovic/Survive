#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/obj/ObjLoader.h"
#include "engine/objects/ObjectShader.h"
#include "engine/entity/Entity2D.h"
#include "engine/renderer/RendererUtil.h"
#include "engine/math/Maths.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    Model model = ObjLoader::loadObj("res/house.obj", loader);
    Texture texture{model, loader.loadTexture("res/house.png")};

    Entity2D entity2D{texture, glm::vec3{0, 0, 0}, 1};

    Camera camera{};
    camera.m_Position = glm::vec3{0, 0, 0};
    camera.m_Yaw = 0;
    camera.m_Pitch = 0;

    ObjectShader shader{};
    shader.start();
    shader.loadProjectionMatrix(Maths::createProjectionMatrix(70, 0.1, 1000));
    ObjectShader::stop();

    float  angle = 0.0f;
    while (display.isRunning())
    {
        Display::clearWindow();

        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_BACK);

        shader.start();
        RendererUtil::prepareEntity(texture);

        shader.loadTransformationMatrix(Maths::createTransformationMatrix(
                glm::vec3{0, -3, -25}, 1, 1, 1, 0, angle));
        angle += 0.1f;
        shader.loadViewMatrix(Maths::createViewMatrix(camera));

        glDrawArrays(GL_TRIANGLES, 0, model.m_VertexCount);

        RendererUtil::finishRenderingEntity();
        ObjectShader::stop();

        display.update();
    }

    return 0;
}
