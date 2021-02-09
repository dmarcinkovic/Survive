//
// Created by david on 10. 01. 2021..
//

#ifndef SURVIVE_BLOOMRENDERER_H
#define SURVIVE_BLOOMRENDERER_H


#include "horizontalBlur/HorizontalBlurRenderer.h"
#include "verticalBlur/VerticalBlurRenderer.h"

class BloomRenderer
{
private:
	HorizontalBlurRenderer m_HorizontalRenderer;
	VerticalBlurRenderer m_VerticalRenderer;

	Loader m_Loader{};
	Model m_Model;

	std::vector<std::reference_wrapper<Object3D>> m_Objects;

public:
	BloomRenderer(int width, int height);

	void render() const;

	void addObject(Object3D &object);

private:
	void prepare() const;

	static void finishRendering();
};


#endif //SURVIVE_BLOOMRENDERER_H
