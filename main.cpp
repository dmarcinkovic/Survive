#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/obj/ObjLoader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/fbo/FrameBuffer.h"
#include "engine/renderer/Renderer2D.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    Texture texture{ObjLoader::loadObj("res/lamp.obj", loader),
                    loader.loadTexture("res/lamp.jpg")};

    Object3D object(texture, glm::vec3{0, -10, -30}, glm::vec3{0, 30, 0});

    Camera camera{};
    Renderer3D renderer;
    renderer.add3DObject(object);

    Light light(glm::vec3{0, 0, 0}, glm::vec3{1, 1, 0.2});
    renderer.addLight(light);

    FrameBuffer frameBuffer;

    Renderer2D renderer2D(loader);
    Entity entity(Texture(renderer2D.getModel(), frameBuffer.attachToDepthBufferTexture()), glm::vec3{0.5, 0.5, 0}, 0.5,
                  0.5);
    renderer2D.addGui(entity);

    ShadowRenderer shadowRenderer;
    shadowRenderer.add3DObject(object);

    while (display.isRunning())
    {
        Display::clearWindow();

        frameBuffer.renderToFrameBuffer(shadowRenderer, camera, light);

        renderer.render(camera);
        renderer2D.render();

        display.update();
    }

    return 0;
}
