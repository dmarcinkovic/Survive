#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
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
    Camera camera;

    Light light(glm::vec3{-10, 10, 10}, glm::vec3{1, 1, 0.2});

    Renderer3D renderer(light);

    Terrain terrain(loader.renderQuad(), glm::vec3{0, -20, -100}, 500, 500, 1);
    terrain.addTextures("res/blendMap.png",
                        {"res/dirt.png", "res/grass.jpeg", "res/rock.png", "res/flowers.png"});
    renderer.addTerrain(terrain);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render(camera);

        display.update();
    }

    return 0;
}
