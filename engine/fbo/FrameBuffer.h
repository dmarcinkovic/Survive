//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_FRAMEBUFFER_H
#define SURVIVE_FRAMEBUFFER_H

#include <GL/glew.h>
#include <vector>

#include "../shadowMapping/ShadowRenderer.h"

class FrameBuffer
{
private:
    constexpr static const int SHADOW_WIDTH = 1024;
    constexpr static const int SHADOW_HEIGHT = 1024;

    GLuint m_FrameBuffer{};
    std::vector<GLuint> m_Textures;
    std::vector<GLuint> m_RenderBuffers;

public:
    FrameBuffer();

    ~FrameBuffer();

    void renderToFrameBuffer(const ShadowRenderer &renderer, const Camera &camera, const Light &light) const;

    GLuint createTexture();

    GLuint attachToDepthBufferTexture();

    void bindFrameBuffer() const;

    static void unbindFrameBuffer();

private:
    void attachDepthComponent(int width, int height);

    GLuint createColorTexture(int width, int height);

    GLuint createDepthTexture(int width, int height);
};


#endif //SURVIVE_FRAMEBUFFER_H
