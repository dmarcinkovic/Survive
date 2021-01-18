//
// Created by david on 29. 12. 2020..
//

#include "MousePicking.h"
#include "../display/Display.h"
#include "../math/Maths.h"

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

			auto[width, height] = Display::getWindowSize<double>();
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

	m_Shader.start();
	glEnable(GL_DEPTH_TEST);

	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));

	for (auto const&[texturedModel, objects] : m_Objects)
	{
		glBindVertexArray(texturedModel.vaoID());
		glEnableVertexAttribArray(0);

		for (auto const &object : objects)
		{
			auto const &o = object.get();
			m_Shader.loadTransformationMatrix(
					Maths::createTransformationMatrix(o.m_Position, o.m_Scale, camera.m_Rotation));

			std::uint8_t r = (o.m_Id & 0x000000FF) >> 0;
			std::uint8_t g = (o.m_Id & 0x0000FF00) >> 8;
			std::uint8_t b = (o.m_Id & 0x00FF0000) >> 16;

			glm::vec4 color(r / 255.0, g / 255.0, b / 255.0, 1.0f);
			color = glm::vec4(1, o.m_Id - 1, 0, 1);

			m_Shader.loadPickingColor(color);

			glDrawArrays(GL_TRIANGLES, 0, o.m_Texture.vertexCount());
		}

		glDisableVertexAttribArray(0);
		Loader::unbindVao();
	}

	glFlush();
	glFinish();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	std::uint8_t data[4];
	glReadPixels(m_MousePosition.x, m_MousePosition.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	MousePickingShader::stop();
	glDisable(GL_DEPTH_TEST);

	mousePressed = false;
}
