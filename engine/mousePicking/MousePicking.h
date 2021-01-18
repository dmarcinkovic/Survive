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
	static bool mousePressed;

	std::unordered_map<TexturedModel, std::vector<std::reference_wrapper<Object3D>>, TextureHash> m_Objects;

	MousePickingShader m_Shader;

	glm::vec2 m_MousePosition{};

public:
	explicit MousePicking();

	void add3DObject(Object3D &entity);

	void render(const Camera &camera) const;

private:
	void mousePressedHandler();

	void renderScene(const std::vector<std::reference_wrapper<Object3D>> &objects, const Camera &camera) const;

	void getRenderedObject() const;

	static glm::vec4 getColor(int id);
};


#endif //SURVIVE_MOUSEPICKING_H
