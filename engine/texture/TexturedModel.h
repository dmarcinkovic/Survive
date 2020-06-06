//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_TEXTUREDMODEL_H
#define SURVIVE_TEXTUREDMODEL_H

#include <GL/glew.h>

#include "../renderer/Loader.h"

class TexturedModel
{
private:
    GLuint m_Vao;
    size_t m_VertexCount;
    GLuint m_TextureID;

public:
    TexturedModel(const Model &model, GLuint textureId);

    TexturedModel() = default;

    void bindTexture() const;

    static void unbindTexture();

    [[nodiscard]] size_t vertexCount() const;

    bool operator==(const TexturedModel &rhs) const;

    friend class TextureHash;
};

struct TextureHash
{
    std::size_t operator()(const TexturedModel &texture) const noexcept
    {
        return texture.m_Vao ^ texture.m_TextureID ^ texture.m_VertexCount;
    }
};


#endif //SURVIVE_TEXTUREDMODEL_H
