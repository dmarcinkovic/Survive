//
// Created by david on 06. 06. 2020..
//

#ifndef SURVIVE_TEXTURE_H
#define SURVIVE_TEXTURE_H


#include <GL/glew.h>

namespace Survive
{
	class Texture
	{
	private:
		GLuint m_TextureId{};

	public:
		explicit Texture(GLuint textureId);

		Texture() = default;

		void bindTexture(int textureIndex) const;

		void bindCubeTexture(int textureIndex) const;

		static void unbindCubeTexture();

		static void unbindTexture();

		[[nodiscard]] GLuint textureId() const;
	};
}

#endif //SURVIVE_TEXTURE_H
