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

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    TexturedModel texture{ObjLoader::loadObj("res/dragon.obj", loader),
                    loader.loadTexture("res/lamp.jpg")};

    Object3D object(texture, glm::vec3{0, -10, -30}, glm::vec3{0, 30, 0});

    Object3D object3D(texture, glm::vec3(20, -10, -30), glm::vec3{0,0,0}, false, 0.5, 0.5);

    Camera camera;
    Light light(glm::vec3{1, 1, 1}, glm::vec3{1, 1, 0.2});

    Renderer3D renderer(light);
    renderer.add3DObject(object);
    renderer.add3DObject(object3D);

    Terrain terrain(loader.renderQuad(), glm::vec3{0, -10, -100}, 100, 100, 1);
    renderer.addTerrain(terrain);

    FrameBuffer frameBuffer;

    ShadowRenderer shadowRenderer;
    shadowRenderer.add3DObject(object);
    shadowRenderer.add3DObject(object3D);
    GLuint shadowMap = frameBuffer.attachToDepthBufferTexture();

    while (display.isRunning())
    {
        Display::clearWindow();

        frameBuffer.renderToFrameBuffer(shadowRenderer, camera, light);

        renderer.render(camera, shadowMap);

        display.update();
    }

    return 0;
}
