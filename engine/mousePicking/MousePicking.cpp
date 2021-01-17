//
// Created by david on 29. 12. 2020..
//

#include <iostream>

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
			m_MousePosition = glm::vec2{mouseX, mouseY};
		}
	});
}

glm::vec3 MousePicking::getNormalizedDeviceCoordinates(const glm::vec2 &viewportCoordinates)
{
	auto[width, height] = Display::getWindowSize<float>();

	float x = (2.0f * viewportCoordinates.x) / width - 1.0f;
	float y = 1.0f - (2.0f * viewportCoordinates.y) / height;

	return glm::vec3{x, y, 1.0f};
}

glm::vec4 MousePicking::getClipCoordinates(const glm::vec3 &normalizedDeviceCoordinates)
{
	return glm::vec4{normalizedDeviceCoordinates.x, normalizedDeviceCoordinates.y, -1.0f, 1.0f};
}

glm::vec4 MousePicking::getEyeCoordinates(const glm::vec4 &clipCoordinates)
{
	glm::vec4 eye = glm::inverse(Maths::projectionMatrix) * clipCoordinates;
	return glm::vec4{eye.x, eye.y, -1.0f, 0.0f};
}

glm::vec3 MousePicking::getWorldCoordinates(const glm::vec4 &eyeCoordinates, const Camera &camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	glm::vec4 world = glm::inverse(viewMatrix) * eyeCoordinates;

	return glm::normalize(glm::vec3{world});
}

//glm::vec3 MousePicking::getMouseRay(double mouseX, double mouseY) const
//{
//	glm::vec2 viewportCoordinates{mouseX, mouseY};
//	glm::vec3 normalizedDeviceCoordinates = getNormalizedDeviceCoordinates(viewportCoordinates);
//	glm::vec4 clipCoordinates = getClipCoordinates(normalizedDeviceCoordinates);
//	glm::vec4 eyeCoordinates = getEyeCoordinates(clipCoordinates);
//	glm::vec3 worldCoordinates = getWorldCoordinates(eyeCoordinates, m_Camera);
//
//	return worldCoordinates;
//}

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

			std::cout << "Loading color: " << color.r << ' ' << color.g << ' ' << color.b << '\n';

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
	std::cout << "Reading color: " << (int)data[0] << ' ' << (int)data[1] << ' ' << (int)data[2] << '\n';

	MousePickingShader::stop();
	glDisable(GL_DEPTH_TEST);

	mousePressed = false;
}
