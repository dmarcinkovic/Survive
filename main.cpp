#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/entity/Entity.h"
#include "engine/math/Maths.h"
#include "engine/objects/ObjectRenderer.h"
#include "engine/light/Light.h"
#include "engine/objects/Object3D.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    Texture texture(Loader::loadTexture("res/lamp.jpg"));

    TexturedModel dragonTexture{ObjParser::loadObj("res/dragon.obj", loader), texture.textureId()};
    TexturedModel lampTexture{ObjParser::loadObj("res/lamp.obj", loader), texture.textureId()};

    Object3D dragon(dragonTexture, glm::vec3{0, -10, -35});
    Object3D lamp(lampTexture, glm::vec3{5, -10, -30});

    Camera camera;
    Light light(glm::vec3{1, 1, 1}, glm::vec3{1, 1, 0.2});

    Renderer3D renderer(light);
    renderer.add3DObject(dragon);
    renderer.add3DObject(lamp);

    renderer.addShadow(dragon);
    renderer.addShadow(lamp);

    Terrain terrain(loader.renderQuad(), glm::vec3{0, -10, -50}, 100, 100, 1);
    renderer.addTerrain(terrain);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render(camera);

        display.update();
    }

    return 0;
}
