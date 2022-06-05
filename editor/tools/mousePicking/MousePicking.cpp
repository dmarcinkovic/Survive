//
// Created by david on 29. 12. 2020..
//

#include <iostream>

#include "MousePicking.h"
#include "Editor.h"
#include "Constants.h"
#include "Components.h"
#include "Maths.h"
#include "Display.h"
#include "PhysicsGizmo.h"

bool Survive::MousePicking::mousePressed = false;
int Survive::MousePicking::selectedEntity = -2;

Survive::MousePicking::MousePicking()
{
	mousePressedHandler();
}

void Survive::MousePicking::mousePressedHandler()
{
	EventHandler::addMouseListener([this](int button, int action, double mouseX, double mouseY) {
		if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if ((Gizmos::isValidOperation() && ImGuizmo::IsOver()) || PhysicsGizmo::isOver() ||
				!Scene::isSceneFocused() || Gizmos::isInsideViewGizmo())
			{
				return;
			}

			setMousePosition(static_cast<float>(mouseX), static_cast<float>(mouseY));
		}
	});
}

glm::vec4 Survive::MousePicking::getColor(std::uint32_t id)
{
	std::uint32_t r = (id & 0x000000FF) >> 0;
	std::uint32_t g = (id & 0x0000FF00) >> 8;
	std::uint32_t b = (id & 0x00FF0000) >> 16;

	return {r / 255.0, g / 255.0, b / 255.0, 1.0f};
}

void Survive::MousePicking::render(entt::registry &registry, const Camera &camera) const
{
	if (!mousePressed)
	{
		return;
	}

	auto entities = prepareEntities(registry);

	setViewport();
	prepareRendering(m_Shader);

	for (auto const &[texturedModel, objects]: entities)
	{
		glBindVertexArray(texturedModel.vaoID());
		glEnableVertexAttribArray(0);

		renderScene(registry, texturedModel, objects, camera);

		glDisableVertexAttribArray(0);
		Loader::unbindVao();
	}

	getRenderedObject();

	finishRendering();

	Display::clearWindow();
	mousePressed = false;

	informListeners(selectedEntity);
}

void Survive::MousePicking::renderScene(const entt::registry &registry, const TexturedModel &texturedModel,
										const std::vector<entt::entity> &objects, const Camera &camera) const
{
	for (auto const &object: objects)
	{
		loadTransformationMatrix(camera, registry, object);

		int id = static_cast<int>(object);
		glm::vec4 color = getColor(id);

		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;

		if (registry.any_of<Render2DComponent>(object))
		{
			projectionMatrix = camera.getOrthographicProjectionMatrix();
			viewMatrix = glm::mat4{1.0f};
		} else
		{
			projectionMatrix = camera.getProjectionMatrix();
			viewMatrix = camera.getViewMatrix();
		}

		m_Shader.loadPickingColor(color);
		m_Shader.loadProjectionMatrix(projectionMatrix);
		m_Shader.loadViewMatrix(viewMatrix);

		glDrawElements(GL_TRIANGLES, texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void Survive::MousePicking::getRenderedObject() const
{
	glFlush();
	glFinish();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	std::uint8_t data[4];

	int x = static_cast<int>(m_MousePosition.x);
	int y = static_cast<int>(m_MousePosition.y);
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	selectedEntity = getEntity(data);

	std::cout << selectedEntity << '\n';
}

int Survive::MousePicking::getEntity(const std::uint8_t *data)
{
	int r = data[0];
	int g = data[1] << 8;
	int b = data[2] << 16;

	glm::ivec4 clearColor = Constants::CLEAR_COLOR * 256.0f;

	if (r == clearColor.r && g == clearColor.g << 8 && b == clearColor.b << 16)
	{
		return -1;
	}

	int entityId = r + g + b;
	return entityId;
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::MousePicking::prepareEntities(entt::registry &registry)
{
	const auto &entities3D = registry.view<Render3DComponent, Transform3DComponent, TagComponent>();
	const auto &entities2D = registry.view<Render2DComponent, Transform3DComponent, TagComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity: entities2D)
	{
		const Render2DComponent &renderComponent = entities2D.get<Render2DComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	for (auto const &entity: entities3D)
	{
		const Render3DComponent &renderComponent = entities3D.get<Render3DComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void Survive::MousePicking::loadTransformationMatrix(const Camera &camera,
													 const entt::registry &registry, entt::entity entity) const
{
	const Transform3DComponent &transform = registry.get<Transform3DComponent>(entity);

	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(transform.position, transform.scale,
																	   transform.rotation);
	m_Shader.loadTransformationMatrix(transformationMatrix);
}

bool Survive::MousePicking::isInsideWindow() const
{
	float width = Scene::getSceneWidth();
	float height = Scene::getSceneHeight();

	auto [regionX, regionY] = Scene::getSceneRegionMin();

	return m_MousePosition.x > 0 && m_MousePosition.x <= width - regionX &&
		   m_MousePosition.y >= regionY && m_MousePosition.y < height;
}

void Survive::MousePicking::setViewport()
{
	auto width = static_cast<GLsizei>(Scene::getSceneWidth());
	auto height = static_cast<GLsizei>(Scene::getSceneHeight());

	glViewport(0, 0, width, height);
}

void Survive::MousePicking::setMousePosition(float mouseX, float mouseY)
{
	float height = Scene::getSceneHeight();
	auto [x, y] = Scene::getScenePosition();
	m_MousePosition = glm::vec2{mouseX - x, height - mouseY + y};

	if (isInsideWindow())
	{
		mousePressed = true;
		selectedEntity = -2;
	}
}

void Survive::MousePicking::addListener(const MousePickingListener &listener)
{
	m_Listeners.emplace_back(listener);
}

void Survive::MousePicking::informListeners(int entity) const
{
	for (const MousePickingListener &listener: m_Listeners)
	{
		listener(entity);
	}
}

void Survive::MousePicking::popListener()
{
	m_Listeners.pop_back();
}
