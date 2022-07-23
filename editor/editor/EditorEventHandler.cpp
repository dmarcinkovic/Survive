//
// Created by david on 14. 03. 2022..
//

#include "EditorEventHandler.h"
#include "Scene.h"
#include "Util.h"
#include "ObjParser.h"

Survive::EditorEventHandler::EditorEventHandler(ContentBrowser &contentBrowser, EntityManager &manager,
												SceneSerializer &sceneLoader)
		: m_ContentBrowser(contentBrowser), m_Manager(manager), m_SceneLoader(sceneLoader)
{

}

void Survive::EditorEventHandler::handleMouseDragging(entt::registry &registry, Renderer &renderer, Loader &loader,
													  const Camera &camera, std::string &savedFile, bool isScenePlaying)
{
	if (!ImGui::IsMouseDragging(ImGuiMouseButton_Left) && m_ContentBrowser.startedDragging())
	{
		if (Scene::isInsideScene())
		{
			std::filesystem::path file = m_ContentBrowser.getDraggedFile();

			if (isScenePlaying)
			{
				std::string message = "Dragging to the scene is not possible while the scene is playing";
				Log::logMessage(LogType::Warn, message);
			} else if (file.has_extension())
			{
				std::string extension = file.extension().string();

				if (extension == ".survive")
				{
					loadScene(registry, savedFile, file);
				} else if (extension == ".obj" && file.has_stem())
				{
					loadModel(registry, loader, file, camera);
				} else if (extension == ".dae" && file.has_stem())
				{
					loadModel(registry, loader, file, camera, true);
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
	m_Manager.setSelectedEntity(registry, -1);

	try
	{
		m_SceneLoader.loadScene(registry, file.string());
		savedFile = file.string();

		Log::logMessage(LogType::Info, "Scene loaded successfully");
	} catch (const std::exception &exception)
	{
		Log::logMessage(LogType::Error, "Failed to load the scene");
	}
}

void Survive::EditorEventHandler::loadModel(entt::registry &registry, Loader &loader,
											const std::filesystem::path &file, const Camera &camera, bool isAnimated)
{
	auto [x, y] = Scene::getScenePosition();
	float width = Scene::getSceneWidth();
	float height = Scene::getSceneHeight();

	try
	{
		DaeParser daeParser;

		Model model;
		if (isAnimated)
		{
			model = daeParser.loadDae(file.string(), loader);
		} else
		{
			model = ObjParser::loadObj(file.string(), loader);
		}

		if (model.isValidModel())
		{
			auto entity = registry.create();
			registry.emplace<TagComponent>(entity, file.stem().string());
			registry.emplace<OutlineComponent>(entity, false);

			if (isAnimated)
			{
				addAnimationComponentToModel(registry, entity, daeParser);
			}

			addRenderComponentToModel(registry, entity, file, model);
			addTransformComponentToModel(registry, entity, camera, x, y, width, height);
		}
	} catch (const std::exception &exception)
	{
		Log::logMessage(LogType::Error, "Error while parsing .obj file");
	}
}

void Survive::EditorEventHandler::loadTexture(entt::registry &registry, Renderer &renderer,
											  const std::filesystem::path &file, Loader &loader)
{
	ImVec2 mousePosition = ImGui::GetMousePos();
	renderer.setMousePickingPosition(mousePosition.x, mousePosition.y);

	registerListener(registry, renderer, file, loader);
}

void Survive::EditorEventHandler::addTransformComponentToModel(entt::registry &registry, entt::entity entity,
															   const Camera &camera, float x, float y,
															   float width, float height)
{
	constexpr float scale = 15.0f;
	glm::vec3 worldSpace = Util::getMouseRay(camera, x, y, width, height) * scale;

	glm::mat4 translate = glm::translate(glm::mat4{1.0f}, camera.getPosition());
	glm::vec3 position = translate * glm::vec4{worldSpace, 1.0f};

	registry.emplace<Transform3DComponent>(entity, position);
}

void Survive::EditorEventHandler::addRenderComponentToModel(entt::registry &registry, entt::entity entity,
															const std::filesystem::path &file, const Model &model)
{
	Render3DComponent renderComponent(TexturedModel(model, Texture()));
	renderComponent.modelName = std::filesystem::relative(file).string();

	registry.emplace<Render3DComponent>(entity, renderComponent);
}

void Survive::EditorEventHandler::registerListener(entt::registry &registry, Renderer &renderer,
												   const std::filesystem::path &file, Loader &loader)
{
	std::string filename = file.string();

	renderer.addMousePickingListener([=, &registry, &renderer, &loader](int selectedEntity) {
		if (selectedEntity < 0)
		{
			renderer.popMousePickingListener();
			return;
		}

		try
		{
			Texture texture = loader.loadTexture(filename.c_str());

			auto entity = static_cast<entt::entity>(selectedEntity);

			if (registry.any_of<Render3DComponent>(entity))
			{
				Render3DComponent &renderComponent = registry.get<Render3DComponent>(entity);

				renderComponent.texturedModel.setTexture(texture);
				renderComponent.textureName = std::filesystem::relative(file).string();
			} else if (registry.any_of<Render2DComponent>(entity))
			{
				Render2DComponent &renderComponent = registry.get<Render2DComponent>(entity);

				renderComponent.texturedModel.setTexture(texture);
				renderComponent.textureName = std::filesystem::relative(file).string();
			}
		} catch (const std::exception &exception)
		{
			Log::logMessage(LogType::Error, "Cannot load texture " + filename);
		}

		renderer.popMousePickingListener();
	});
}

void Survive::EditorEventHandler::addAnimationComponentToModel(entt::registry &registry, entt::entity entity,
															   const DaeParser &parser)
{
	auto[rootJoint, numberOfJoints] = parser.getJointData();
	if (numberOfJoints > 0)
	{
		Animator animator(parser.getAnimation());
		registry.emplace<AnimationComponent>(entity, std::move(animator), rootJoint, numberOfJoints);
	}
}
