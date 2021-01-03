#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include "engine/display/Display.h"
#include "editor/fileChooser/FileChooser.h"

int main()
{
	constexpr int width = 1200;
	constexpr int height = 800;

	Display display(width, height, "Survive");

	bool openItemSelected = false;

	while (display.isRunning())
	{
		Display::clearWindow();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("Open", "Ctrl+O", &openItemSelected);
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		FileChooser::open();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		display.update();
	}

	return 0;
}
