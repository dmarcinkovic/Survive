//
// Created by david on 17. 10. 2020..
//

#ifndef SURVIVE_WATERFBO_H
#define SURVIVE_WATERFBO_H


#include <GL/glew.h>
#include "../../core/fbo/FrameBuffer.h"

namespace Survive
{
	class WaterFbo
	{
	private:
		constexpr static const int REFLECTION_WIDTH = 320;
		constexpr static const int REFLECTION_HEIGHT = 180;
		constexpr static const int REFRACTION_WIDTH = 1280;
		constexpr static const int REFRACTION_HEIGHT = 720;

		Texture m_ReflectionColorTexture{};
		Texture m_RefractionColorTexture{};
		Texture m_RefractionDepthTexture{};

		FrameBuffer m_FboReflection;
		FrameBuffer m_FboRefraction;

	public:
		WaterFbo();

		[[nodiscard]] const Texture &reflectionColorTexture() const;

		[[nodiscard]] const Texture &refractionColorTexture() const;

		[[nodiscard]] const Texture &getRefractionDepthBuffer() const;

		void bindReflectionFrameBuffer() const;

		void bindRefractionFrameBuffer() const;

		static void unbindFrameBuffer();

	private:
		void initializeRefractionFrameBuffer();

		void initializeReflectionFrameBuffer();
	};
}

#endif //SURVIVE_WATERFBO_H
