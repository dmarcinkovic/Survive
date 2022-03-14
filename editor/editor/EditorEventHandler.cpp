//
// Created by david on 14. 03. 2022..
//

#include "EditorEventHandler.h"
#include "Scene.h"

Survive::EditorEventHandler::EditorEventHandler(ContentBrowser &contentBrowser, EntityManager &manager,
												SceneSerializer &sceneLoader)
		: m_ContentBrowser(contentBrowser), m_Manager(manager), m_SceneLoader(sceneLoader)
{

}

void Survive::EditorEventHandler::handleMouseDragging(entt::registry &registry, Renderer &renderer, Loader &loader,
													  const Camera &camera, std::string &savedFile)
{
	if (!ImGui::IsMouseDragging(ImGuiMouseButton_Left) && m_ContentBrowser.startedDragging())
	{
		if (Scene::isInsideScene())
		{
			std::filesystem::path file = m_ContentBrowser.getDraggedFile();

			if (file.has_extension())
			{
				std::string extension = file.extension().string();

				if (extension == ".survive")
				{
					loadScene(registry, savedFile, file);
				} else if (extension == ".obj" && file.has_stem())
				{
					loadModel(registry, loader, file, camera);
				} else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
				{
					loadTexture(registry, renderer, file, loader);
				}
			}
		}

		m_ContentBrowser.stopDragging();
	}
}

void Survive::EditorEventHandler::loadScene(entt::registry &registry, std::string &savedFile,
											const std::filesystem::path &file)
{
	m_Manager.setSelectedEntity(-1);

	try
	{
		m_SceneLoader.loadScene(registry, file.string());
		savedFile = file.string();

		Log::logMessage(LogType::INFO, "Scene loaded successfully");
	} catch (const std::exception &exception)
	{
		Log::logMessage(LogType::ERROR, "Failed to load the scene");
	}
}

void Survive::EditorEventHandler::loadModel(entt::registry &registry, Loader &loader,
											const std::filesystem::path &file, const Camera &camera)
{
	auto[x, y] = Scene::getScenePosition();
	float width = Scene::getSceneWidth();
	float height = Scene::getSceneHeight();

	EditorUtil::loadDraggedModels(registry, loader, file, camera, x, y, width, height);
}

void Survive::EditorEventHandler::loadTexture(entt::registry &registry, Survive::Renderer &renderer,
											  const std::filesystem::path &file, Survive::Loader &loader)
{
	ImVec2 mousePosition = ImGui::GetMousePos();
	renderer.setMousePickingPosition(mousePosition.x, mousePosition.y);

	EditorUtil::registerListener(registry, renderer, file, loader);
}
