#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/DaeParser.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    TexturedModel texturedModel(DaeParser::loadDae("res/character.dae", loader),
                                Loader::loadTexture("res/character.png"));

    Object3D object(texturedModel, glm::vec3{0, -10, -30}, glm::vec3{-90, 0, 0});

    Camera camera{};
    Light light(glm::vec3{10, 10, 10}, glm::vec3{1, 1, 1});

    Renderer3D renderer(light);
    renderer.addAnimatedObject(object);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render(camera);

        display.update();
    }

    return 0;
}
