#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/obj/ObjLoader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    Texture texture{ObjLoader::loadObj("res/stall.obj", loader),
                    loader.loadTexture("res/stall.png")};

    Object3D object(texture, glm::vec3{0, -10, -30}, glm::vec3{0, 30, 0});

    Camera camera{};
    ObjectRenderer renderer;
    renderer.add3DObject(object);

    Light light(glm::vec3{-10, 10, 10}, glm::vec3{1, 1, 0.2});
    renderer.setLight(light);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render(camera);

        display.update();
    }

    return 0;
}
