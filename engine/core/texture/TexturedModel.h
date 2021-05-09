//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_TEXTUREDMODEL_H
#define SURVIVE_TEXTUREDMODEL_H

#include <GL/glew.h>

#include "Texture.h"
#include "Loader.h"

namespace Survive
{
	class TexturedModel
	{
	private:
		GLuint m_Vao{};
		GLsizei m_VertexCount{};
		Texture m_Texture;

	public:
		TexturedModel(const Model &model, const Texture &texture);

		TexturedModel();

		void bind() const;

		void bindTexture(int index) const;

		void bindCubeTexture(int index) const;

		static void unbind();

		static void unbindVao();

		[[nodiscard]] const Texture &getTexture() const;

		[[nodiscard]] GLuint vaoID() const;

		void setVertexCount(int vertexCount);

		[[nodiscard]] GLsizei vertexCount() const;

		bool operator==(const TexturedModel &rhs) const;

		[[nodiscard]] bool isValidTexture() const;

		friend class TextureHash;
	};

	struct TextureHash
	{
		std::size_t operator()(const TexturedModel &texture) const noexcept
		{
			return texture.m_Vao ^ texture.m_Texture.textureId() ^ texture.m_VertexCount;
		}
	};
}

#endif //SURVIVE_TEXTUREDMODEL_H