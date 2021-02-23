//
// Created by david on 17. 10. 2020..
//

#ifndef SURVIVE_WATERFBO_H
#define SURVIVE_WATERFBO_H


#include <GL/glew.h>
#include "../fbo/FrameBuffer.h"

class WaterFbo
{
private:
	constexpr static const int REFLECTION_WIDTH = 320;
	constexpr static const int REFLECTION_HEIGHT = 180;
	constexpr static const int REFRACTION_WIDTH = 1280;
	constexpr static const int REFRACTION_HEIGHT = 720;

	GLuint m_ReflectionColorTexture{};
	GLuint m_RefractionColorTexture{};
	GLuint m_RefractionDepthTexture{};

	FrameBuffer m_FboReflection;
	FrameBuffer m_FboRefraction;

public:
	WaterFbo();

	[[nodiscard]] GLuint reflectionColorTexture() const;

	[[nodiscard]] GLuint refractionColorTexture() const;

	[[nodiscard]] GLuint getRefractionDepthBuffer() const;

	void bindReflectionFrameBuffer() const;

	void bindRefractionFrameBuffer() const;

	static void unbindFrameBuffer();

private:
	void initializeRefractionFrameBuffer();

	void initializeReflectionFrameBuffer();
};


#endif //SURVIVE_WATERFBO_H
