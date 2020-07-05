#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/Texture.h"
#include "engine/renderer/Renderer2D.h"
#include "engine/physics/World.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
    Renderer2D renderer(loader);

    Texture circleTexture(renderer.getModel(), loader.loadTexture("res/circle.png"));
    Texture rectangleTexture(renderer.getModel(), loader.loadTexture("res/rectangle.png"));

    Entity2D circle(circleTexture, glm::vec3{0.5, 0.25, 0.0}, 0.1);
    Entity2D rectangle(rectangleTexture, glm::vec3{-0.5, -0.5, 0.0}, 0.3);

    World world;
    world.addBody(std::make_unique<Circle>(circle, 0.1, 10, BodyType::DYNAMIC, glm::vec2{-0.01, 0}));
    world.addBody(std::make_unique<Rectangle>(rectangle, 0.2, 0.4, 1, BodyType::STATIC));

    renderer.addGui(circle);
    renderer.addGui(rectangle);

    while (display.isRunning())
    {
        Display::clearWindow();

        world.step();
        renderer.render();

        display.update();
    }

    return 0;
}
