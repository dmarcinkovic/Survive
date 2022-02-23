//
// Created by david on 24. 01. 2022..
//

#ifndef SURVIVE_WIREFRAMERENDERER_H
#define SURVIVE_WIREFRAMERENDERER_H

#include "WireframeShader.h"
#include "Loader.h"
#include "Renderer3D.h"

namespace Survive
{
	class WireframeRenderer : public Renderer3D
	{
	private:
		static constexpr int MAX_VERTICES = 100'000;

		WireframeShader m_Shader;

		Loader m_Loader;
		Model m_Model;

		static std::vector<float> m_Vertices;
		static GLuint m_Vbo;

	public:
		WireframeRenderer();

		void render() const;

		static void updateData(std::vector<float> vertices);

	private:
		void prepare() const;

		static void finish();
	};
}

#endif //SURVIVE_WIREFRAMERENDERER_H
