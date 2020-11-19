#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/TexturedModel.h"
#include "engine/objects/Object3D.h"
#include "engine/camera/Camera.h"
#include "engine/light/Light.h"
#include "engine/renderer/Renderer3D.h"
#include "engine/parser/ObjParser.h"


void ShowExampleAppDockSpace(bool* p_open)
{
	// In 99% case you should be able to just call DockSpaceOverViewport() and ignore all the code below!
	// In this specific demo, we are not using DockSpaceOverViewport() because:
	// - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
	// - we allow the host window to have padding (when opt_padding == true)
	// - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
	// TL;DR; this demo is more complicated than what you would normally use.
	// If we removed all the options we are showcasing, this demo would become:
	//     void ShowExampleAppDockSpace()
	//     {
	//         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	//     }

	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", p_open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::End();
}

int main()
{
	constexpr int width = 1200;
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

	Terrain terrain(loader.renderQuad(), glm::vec3{0, -10, -50}, 100, 100, 1);
	renderer.addTerrain(terrain);

	bool showDemoWindow = true;
	bool showAnotherWindow = false;
	ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (display.isRunning())
	{
		Display::clearWindow();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = static_cast<unsigned>(io.ConfigFlags) | ImGuiConfigFlags_DockingEnable;

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
//		ShowExampleAppDockSpace(&showDemoWindow);

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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
			ImGui::Begin("Scene window");
			ImVec2 pos = ImGui::GetCursorScreenPos();
			auto textureId = reinterpret_cast<ImTextureID>(renderer.getRenderedTexture());

			ImVec2 windowSize = ImGui::GetWindowSize();

			ImGui::GetWindowDrawList()->AddImage(textureId, pos,
												 ImVec2(pos.x + windowSize.x, pos.y + windowSize.y), ImVec2(0, 1),
												 ImVec2(1, 0));

			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		renderer.renderToFbo(camera);

		display.update();
	}

	return 0;
}
