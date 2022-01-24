//
// Created by david on 24. 01. 2022..
//

#ifndef SURVIVE_WIREFRAMERENDERER_H
#define SURVIVE_WIREFRAMERENDERER_H

#include "WireframeShader.h"
#include "Loader.h"

namespace Survive
{
	class WireframeRenderer
	{
	private:
		WireframeShader m_Shader;

		Loader m_Loader;

		Model m_Model;
		GLuint m_Vbo{};

	public:
		WireframeRenderer();

		void render() const;
	};
}

#endif //SURVIVE_WIREFRAMERENDERER_H
