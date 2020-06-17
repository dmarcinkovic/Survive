//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_TEXTURE_H
#define SURVIVE_TEXTURE_H

#include <GL/glew.h>

#include "../renderer/Loader.h"

class Texture
{
private:
    GLuint m_Vao;
    size_t m_VertexCount;
    GLuint m_TextureID;

public:
    Texture(const Model &model, GLuint textureId);

    Texture() = default;

    void bindTexture() const;

    static void unbindTexture();

    [[nodiscard]] size_t vertexCount() const;

    bool operator==(const Texture &rhs) const;

    friend class TextureHash;

    [[nodiscard]] bool isValidTexture() const;
};

struct TextureHash
{
    std::size_t operator()(const Texture &texture) const noexcept
    {
        return texture.m_Vao ^ texture.m_TextureID ^ texture.m_VertexCount;
    }
};


#endif //SURVIVE_TEXTURE_H
