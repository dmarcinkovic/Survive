#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/TexturedModel.h"
#include "engine/parser/DaeParser.h"
#include "engine/objects/Object3D.h"
#include "engine/camera/Camera.h"
#include "engine/light/Light.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/renderer/Renderer2D.h"

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
	Light light(glm::vec3{0, 10, -10}, glm::vec3{1, 1, 1});

	Renderer3D renderer(light);
	renderer.addAnimatedObject(object);

	Entity entity(TexturedModel(loader.renderQuad(), renderer.getRenderedTexture()), glm::vec3{0.5, 0.5, 0}, 0.5, 0.5);
	Renderer2D renderer2D(loader);

	renderer2D.addGui(entity);

	bool showDemoWindow = true;
	bool showAnotherWindow = false;
	ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (display.isRunning())
	{
		Display::clearWindow();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");

			ImGui::Text("This is some useful text.");
			ImGui::Checkbox("Demo Window", &showDemoWindow);
			ImGui::Checkbox("Another Window", &showAnotherWindow);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", reinterpret_cast<float *>(&clearColor));

			if (ImGui::Button("Button"))
			{
				counter++;
			}

			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
						ImGui::GetIO().Framerate);
			ImGui::End();
		}

		{
//            ImGui::Begin("Scene window");
//            ImVec2 pos = ImGui::GetCursorScreenPos();

//            ImGui::GetWindowDrawList()->AddImage();

//            ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		renderer.renderToFbo(camera);
		renderer.render(camera);

		renderer2D.render();

		display.update();
	}

	return 0;
}
