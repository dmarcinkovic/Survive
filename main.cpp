#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"
#include "engine/parser/ObjParser.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    TexturedModel texture{ObjParser::loadObj("res/cube.obj", loader),
                    loader.loadTexture("res/lamp.jpg")};

    Object3D object(texture, glm::vec3{0, 0, -5}, glm::vec3{0, 30, 0});

    Camera camera{};
    Light light(glm::vec3{0, 1000000, 1000000}, glm::vec3{1, 1, 0.2});
    ObjectRenderer renderer(light);
    renderer.add3DObject(object);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render(camera, 0);

        display.update();
    }

    return 0;
}
