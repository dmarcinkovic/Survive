//
// Created by david on 19. 12. 2020..
//

#ifndef SURVIVE_BLURRENDERER_H
#define SURVIVE_BLURRENDERER_H

#include <functional>
#include <unordered_map>

#include "../texture/TexturedModel.h"
#include "../objects/Object3D.h"
#include "../fbo/FrameBuffer.h"
#include "horizontalBlur/HorizontalBlurRenderer.h"
#include "verticalBlur/VerticalBlurRenderer.h"
#include "../objects/ObjectRenderer.h"

class BlurRenderer
{
private:
	ObjectRenderer m_ObjectRenderer;
	Loader m_Loader;
	FrameBuffer m_Fbo;
	Model m_Model;

	Texture m_Texture;

	HorizontalBlurRenderer m_HorizontalBlurRenderer;
	VerticalBlurRenderer m_VerticalBlurRenderer;

public:
	BlurRenderer(const Light &light, int width, int height);

	void render(const Camera &camera) const;

	const Texture &getTexture() const;

	void addObject(Object3D &object);

private:
	void prepareRendering() const;

	static void finishRendering();
};


#endif //SURVIVE_BLURRENDERER_H
