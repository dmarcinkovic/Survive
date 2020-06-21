#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/Texture.h"
#include "engine/renderer/Renderer2D.h"
#include "engine/physics/collision/Circle.h"
#include "engine/physics/collision/Rectangle.h"
#include "engine/physics/World.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
    Renderer2D renderer(loader);

    Texture texture(renderer.getModel(), loader.loadTexture("res/circle.png"));
    Texture texture1(renderer.getModel(), loader.loadTexture("res/circle.png"));

    Entity2D entity1(texture, glm::vec3{-0.5, 0.5, 0.0}, 0.3);
    Entity2D entity2(texture, glm::vec3{0.5, 0.25, 0.0}, 0.1);
    Entity2D entity3(texture1, glm::vec3{-0.5, -0.5, 0.0}, 0.3);

    World world;
    world.addBody(std::make_unique<Circle>(entity1, 0.3, 5, BodyType::STATIC));
    world.addBody(std::make_unique<Circle>(entity2, 0.1, 1, BodyType::DYNAMIC, glm::vec2{-0.01, 0}));
//    world.addBody(std::make_unique<Rectangle>(entity3, 0.2, 0.4, 1, BodyType::STATIC));

//    world.step();
//    world.step();

    renderer.addGui(entity1);
    renderer.addGui(entity2);

    while (display.isRunning())
    {
        Display::clearWindow();

        world.step();
        renderer.render();

        display.update();
    }

    return 0;
}
