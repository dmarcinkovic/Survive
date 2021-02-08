//
// Created by david on 29. 12. 2020..
//

#include <iostream>
#include "MousePicking.h"
#include "../display/Display.h"
#include "../math/Maths.h"
#include "../renderer/Renderer3DUtil.h"

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

void MousePicking::add3DObject(Object3D &entity)
{
	auto &batch = m_Objects[entity.m_Texture];
	batch.emplace_back(entity);
}

glm::vec4 MousePicking::getColor(int id)
{
	int r = (id & 0x000000FF) >> 0;
	int g = (id & 0x0000FF00) >> 8;
	int b = (id & 0x00FF0000) >> 16;

	return glm::vec4(r / 255.0, g / 255.0, b / 255.0, 1.0f);
}

void MousePicking::render(const Camera &camera) const
{
	if (!mousePressed)
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_Shader);

	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));

	for (auto const&[texturedModel, objects] : m_Objects)
	{
		glBindVertexArray(texturedModel.vaoID());
		glEnableVertexAttribArray(0);

		renderScene(objects, camera);

		glDisableVertexAttribArray(0);
		Loader::unbindVao();
	}

	getRenderedObject();

	Renderer3DUtil::finishRendering();

	Display::clearWindow();

	mousePressed = false;
}

void MousePicking::renderScene(const std::vector<std::reference_wrapper<Object3D>> &objects, const Camera &camera) const
{
	for (auto const &object : objects)
	{
		auto const &o = object.get();
		m_Shader.loadTransformationMatrix(
				Maths::createTransformationMatrix(o.m_Position, o.m_Scale, camera.rotation));

		glm::vec4 color = getColor(o.m_Id);
		m_Shader.loadPickingColor(color);

		glDrawArrays(GL_TRIANGLES, 0, o.m_Texture.vertexCount());
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

	if (r == 0xFF && g == 0xFF00 && b == 0xFF0000)
	{
		return 0;
	}

	return r + g + b;
}
