//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_FRAMEBUFFER_H
#define SURVIVE_FRAMEBUFFER_H

#include <GL/glew.h>
#include <vector>

#include "../shadowMapping/ShadowRenderer.h"
#include "../../ecs/entt.hpp"

class FrameBuffer
{
private:
	GLuint m_FrameBuffer{};
	std::vector<GLuint> m_Textures;
	std::vector<GLuint> m_RenderBuffers;

public:
	FrameBuffer();

	~FrameBuffer();

	void renderToFrameBuffer(entt::registry &registry, const ShadowRenderer &renderer, const Camera &camera,
							 const Light &light, int width, int height) const;

	GLuint createTexture();

	GLuint attachColorComponent(int width, int height);

	GLuint attachToDepthBufferTexture(int width, int height);

	void bindFrameBuffer() const;

	void bindDrawBuffer() const;

	static void unbindFrameBuffer();

	static void unbindDrawFrameBuffer();

	GLuint createColorTexture(int width, int height);

	static void attachColorAttachment(GLuint texture);

	static void drawBuffer();

	[[nodiscard]] GLuint getRenderBuffer(int renderBufferNumber) const;

	void attachDepthComponent(int width, int height);

	GLuint createDepthTexture(int width, int height);

	GLuint createDepthTextureAttachment(int width, int height);
};


#endif //SURVIVE_FRAMEBUFFER_H
