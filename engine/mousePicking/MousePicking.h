//
// Created by david on 29. 12. 2020..
//

#ifndef SURVIVE_MOUSEPICKING_H
#define SURVIVE_MOUSEPICKING_H

#include <glm/glm.hpp>
#include <unordered_map>
#include <functional>

#include "../camera/Camera.h"
#include "../texture/TexturedModel.h"
#include "../objects/Object3D.h"
#include "MousePickingShader.h"

class MousePicking
{
private:
	const Camera &m_Camera;
	std::unordered_map<TexturedModel, std::vector<std::reference_wrapper<Object3D>>, TextureHash> m_Objects;

	MousePickingShader m_Shader;

public:
	explicit MousePicking(const Camera &camera);

	void add3DObject(Object3D &entity);

private:
	void mousePressedHandler();

	static glm::vec3 getNormalizedDeviceCoordinates(const glm::vec2 &viewportCoordinates);

	static glm::vec4 getClipCoordinates(const glm::vec3 &normalizedDeviceCoordinates);

	static glm::vec4 getEyeCoordinates(const glm::vec4 &clipCoordinates);

	static glm::vec3 getWorldCoordinates(const glm::vec4 &eyeCoordinates, const Camera &camera);

	[[nodiscard]] glm::vec3 getMouseRay(double mouseX, double mouseY) const;

	static glm::vec4 getColor(int id);
};


#endif //SURVIVE_MOUSEPICKING_H
