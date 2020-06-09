#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/obj/ObjLoader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"
#include "engine/renderer/Renderer3D.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    TexturedModel texture{ObjLoader::loadObj("res/character.obj", loader),
                          loader.loadTexture("res/character.png")};

    Object3D object(texture, glm::vec3{0, -10, -30}, glm::vec3{0, 30, 0});

    Camera camera{};
    Light light(glm::vec3{-10, 10, 10}, glm::vec3{1, 1, 1});

    Renderer3D renderer(light);
    renderer.add3DObject(object);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render(camera);

        display.update();
    }

    return 0;
}
