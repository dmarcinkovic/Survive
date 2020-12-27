//
// Created by david on 27. 12. 2020..
//

#ifndef SURVIVE_OUTLINERENDERER_H
#define SURVIVE_OUTLINERENDERER_H

#include <functional>
#include <unordered_map>

#include "OutlineShader.h"
#include "../texture/TexturedModel.h"
#include "../objects/Object3D.h"
#include "../light/Light.h"
#include "../camera/Camera.h"

class OutlineRenderer
{
private:
	OutlineShader m_Shader;
	std::unordered_map<TexturedModel, std::vector<std::reference_wrapper<Object3D>>, TextureHash> m_Objects;

	const Light &m_Light;

public:
	explicit OutlineRenderer(const Light &light);

	void render(const Camera &camera) const;

	void add3DObject(Object3D &object);
};


#endif //SURVIVE_OUTLINERENDERER_H
