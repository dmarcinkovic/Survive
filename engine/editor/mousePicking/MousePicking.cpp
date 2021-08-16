//
// Created by david on 29. 12. 2020..
//

#include <iostream>

#include "MousePicking.h"
#include "Editor.h"
#include "Constants.h"
#include "Components.h"
#include "Maths.h"
#include "Renderer3DUtil.h"
#include "Display.h"

bool Survive::MousePicking::mousePressed = false;

Survive::MousePicking::MousePicking()
{
	mousePressedHandler();
}

void Survive::MousePicking::mousePressedHandler()
{
	EventHandler::addMouseListener([this](int button, int action, double mouseX, double mouseY) {
		if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
		{
			mousePressed = true;

			float height = Editor::getSceneHeight();
			auto[x, y] = Editor::getScenePosition();
 			m_MousePosition = glm::vec2{mouseX - x, height - mouseY + y};
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
	if (!mousePressed || !isInsideWindow())
	{
		return;
	}

	float width = Editor::getSceneWidth();
	float height = Editor::getSceneHeight();
	glViewport(0, 0, width, height);

	auto entities = prepareEntities(registry);

	Renderer3DUtil::prepareRendering(m_Shader);

	m_Shader.loadProjectionMatrix(camera.getProjectionMatrix());
	m_Shader.loadViewMatrix(camera.getViewMatrix());

	for (auto const&[texturedModel, objects] : entities)
	{
		glBindVertexArray(texturedModel.vaoID());
		glEnableVertexAttribArray(0);

		renderScene(registry, objects, camera);

		glDisableVertexAttribArray(0);
		Loader::unbindVao();
	}

	getRenderedObject();

	Renderer3DUtil::finishRendering();

	Display::clearWindow();

	mousePressed = false;
}

void Survive::MousePicking::renderScene(const entt::registry &registry, const std::vector<entt::entity> &objects,
										const Camera &camera) const
{
	for (auto const &object : objects)
	{
		loadTransformationMatrix(camera, registry, object);

		int id = static_cast<int>(object);
		glm::vec4 color = getColor(id);

		m_Shader.loadPickingColor(color);

		const Render3DComponent &renderComponent = registry.get<Render3DComponent>(object);
		glDrawArrays(GL_TRIANGLES, 0, renderComponent.texturedModel.vertexCount());
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
	glReadPixels(x, y, 1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int id = getID(data);
	std::cout << id << '\n';
}

int Survive::MousePicking::getID(const std::uint8_t *data)
{
	int r = data[0];
	int g = data[1] << 8;
	int b = data[2] << 16;

	glm::ivec4 clearColor = Constants::CLEAR_COLOR * 256.0f;

	if (r == clearColor.r && g == clearColor.g << 8 && b == clearColor.b << 16)
	{
		return 0;
	}

	return r + g + b;
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::MousePicking::prepareEntities(entt::registry &registry)
{
	const auto &entities3D = registry.view<Render3DComponent, Transform3DComponent, IdComponent>();
	const auto &entities2D = registry.view<Render3DComponent, Transform3DComponent, IdComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : entities2D)
	{
		const Render3DComponent &renderComponent = entities2D.get<Render3DComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	for (auto const &entity : entities3D)
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

	glm::vec3 rotation = camera.rotation + transform.rotation;

	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
	m_Shader.loadTransformationMatrix(transformationMatrix);
}

bool Survive::MousePicking::isInsideWindow() const
{
	float width = Editor::getSceneWidth();
	float height = Editor::getSceneHeight();

	return m_MousePosition.x >= 0 && m_MousePosition.x <= width &&
			m_MousePosition.y >= 0 && m_MousePosition.y <= height;
}
