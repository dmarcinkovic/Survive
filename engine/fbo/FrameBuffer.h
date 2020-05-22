//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_FRAMEBUFFER_H
#define SURVIVE_FRAMEBUFFER_H


#include <GL/glew.h>
#include <vector>
#include "../renderer/Renderer3D.h"

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

    void renderToFrameBuffer(const Renderer3D &renderer, const Camera &camera) const;

    GLuint createTexture();

    GLuint attachToDepthBufferTexture();

private:
    void attachDepthComponent(int width, int height);

    static void unbindFrameBuffer();

    void bindFrameBuffer() const;

    GLuint createColorTexture(int width, int height);

    GLuint createDepthTexture(int width, int height);
};


#endif //SURVIVE_FRAMEBUFFER_H
