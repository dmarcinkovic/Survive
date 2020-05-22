#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/obj/ObjLoader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/gui/GuiRenderer.h"
#include "engine/renderer/Renderer2D.h"
#include "engine/fbo/FrameBuffer.h"

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

    Light light(glm::vec3{-10, 10, 10}, glm::vec3{1, 1, 0.2});
    renderer.addLight(light);

    FrameBuffer frameBuffer;

    Renderer2D renderer2D(loader);
    Texture texture1(renderer2D.getModel(), frameBuffer.createTexture());
    Entity entity(texture1, glm::vec3{0.5, 0.5, 0}, 0.5, 0.5);
    renderer2D.addGui(entity);

    while (display.isRunning())
    {
        frameBuffer.bindFrameBuffer();
        Display::clearWindow();
        renderer.render(camera);
        FrameBuffer::unbindFrameBuffer();

        Display::clearWindow();
        renderer.render(camera);
        renderer2D.render();

        display.update();
    }

    return 0;
}
