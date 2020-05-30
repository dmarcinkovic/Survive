#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/Texture.h"
#include "engine/renderer/Renderer2D.h"
#include "engine/ui/button/Button.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
    Renderer2D renderer(loader);

//    Texture texture(renderer.getModel(), 1);
//
//    Button button(texture, glm::vec3{0, 0.5, 0}, 0.4, 0.2,
//                  glm::vec4{1, 0, 0, 0.6}, "Button1");
//    Button button2(texture, glm::vec3{0, 0, 0}, 0.3, 0.1,
//                   glm::vec4{0, 1, 0, 0.4}, "Button2");
//
//    renderer.addButton(button);
//    renderer.addButton(button2);
    Font font("res/candara.png", loader);
    font.loadFontFromFntFile("res/candara.fnt");

    Text text("D", font, glm::vec3{0, 0, 0}, glm::vec3{1, 0, 1}, 10.0);
    text.centerText();
    text.addBorder(0.5, glm::vec3{1, 0, 0});

    Text text2("David", font, glm::vec3{0, 0.25, 0}, glm::vec3{1, 0, 0}, 3);
    text2.addBorder(0.5, glm::vec3{0, 1, 0});
    text2.centerText();

    renderer.addText(text);
    renderer.addText(text2);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
