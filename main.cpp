#include <iostream>
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

    Texture texture(renderer.getModel(),loader.loadTexture("res/apple.png"));
    Texture texture1(renderer.getModel(),loader.loadTexture("res/texture.jpg"));

    Entity2D entity1(texture, glm::vec3{-0.5, 0.5, 0.0}, 0.3);
    Entity2D entity2(texture, glm::vec3{0.5, 0.5, 0.0}, 0.3);
    Entity2D entity3(texture1, glm::vec3{-0.5, -0.5, 0.0}, 0.3);

    World world;
    world.addBody(std::make_unique<Circle>(entity1, 10, BodyType::DYNAMIC));
    world.addBody(std::make_unique<Rectangle>(entity3, 10, 12, BodyType::STATIC));
    world.addBody(std::make_unique<Circle>(entity2, 15, BodyType::DYNAMIC));

    world.step();

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
