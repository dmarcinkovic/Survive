//
// Created by david on 29. 12. 2020..
//

#include <iostream>
#include "MousePicking.h"
#include "../display/Display.h"
#include "../math/Maths.h"
#include "../renderer/Renderer3DUtil.h"
#include "../constant/Constants.h"
#include "../components/Components.h"

bool MousePicking::mousePressed = false;

MousePicking::MousePicking()
{
	mousePressedHandler();
}

void MousePicking::mousePressedHandler()
{
	Display::addMouseListener([this](int button, int action, double mouseX, double mouseY) {
		if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
		{
			mousePressed = true;

			int height = Display::getHeight();
			m_MousePosition = glm::vec2{mouseX, height - mouseY};
		}
	});
}

glm::vec4 MousePicking::getColor(int id)
{
	int r = (id & 0x000000FF) >> 0;
	int g = (id & 0x0000FF00) >> 8;
	int b = (id & 0x00FF0000) >> 16;

	return glm::vec4(r / 255.0, g / 255.0, b / 255.0, 1.0f);
}

void MousePicking::render(entt::registry  &registry, const Camera &camera) const
{
	if (!mousePressed)
	{
		return;
	}

	auto entities = prepareEntities(registry);

	Renderer3DUtil::prepareRendering(m_Shader);

	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));

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

void MousePicking::renderScene(entt::registry &registry, const std::vector<entt::entity> &objects, const Camera &camera) const
{
	for (auto const &object : objects)
	{
		loadTransformationMatrix(camera, registry, object);

		IdComponent id = registry.get<IdComponent>(object);
		glm::vec4 color = getColor(id.id);
		m_Shader.loadPickingColor(color);

		RenderComponent renderComponent = registry.get<RenderComponent>(object);
		glDrawArrays(GL_TRIANGLES, 0, renderComponent.texturedModel.vertexCount());
	}
}

void MousePicking::getRenderedObject() const
{
	glFlush();
	glFinish();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	std::uint8_t data[4];
	glReadPixels(m_MousePosition.x, m_MousePosition.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int id = getID(data);
	std::cout << id << '\n';
}

int MousePicking::getID(const std::uint8_t *data)
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

std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
MousePicking::prepareEntities(entt::registry &registry)
{
	auto entities3D = registry.group<RenderComponent, Transform3DComponent, IdComponent>();
	auto entities2D = registry.group<RenderComponent, Transform2DComponent, IdComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : entities2D)
	{
		RenderComponent renderComponent = entities2D.get<RenderComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	for (auto const &entity : entities3D)
	{
		RenderComponent renderComponent = entities3D.get<RenderComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void MousePicking::loadTransformationMatrix(const Camera &camera, entt::registry &registry, entt::entity entity) const
{
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation = camera.m_Rotation;

	if (registry.has<Transform2DComponent>(entity))
	{
			Transform2DComponent transform = registry.get<Transform2DComponent>(entity);

			position = glm::vec3{transform.position.x, transform.position.y, 0};
			scale = glm::vec3{transform.scale.x, transform.scale.y, 1};
			rotation += glm::vec3{transform.rotation.x, transform.rotation.y, 0};
	} else
	{
		Transform3DComponent transform = registry.get<Transform3DComponent>(entity);

		position = transform.position;
		scale = transform.scale;
		rotation += transform.rotation;
	}

	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(position, scale, rotation);
	m_Shader.loadTransformationMatrix(transformationMatrix);
}
