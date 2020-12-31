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
	static constexpr float SCALE = 1.04f;

	OutlineShader m_Shader;
	Object3D *m_Object{};

public:
	void render(const Camera &camera) const;

	void add3DObject(Object3D &object);

	void removeObject();

private:
	static void setStencilFunctions();

	static void resetStencilFunctions();

	void loadUniforms(const Camera &camera) const;

	void prepareObject() const;

	static void finishRenderingObject();
};


#endif //SURVIVE_OUTLINERENDERER_H
