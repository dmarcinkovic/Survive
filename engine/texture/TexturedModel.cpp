//
// Created by david on 24. 03. 2020..
//

#include "TexturedModel.h"

TexturedModel::TexturedModel(const Model &model, GLuint textureId)
        : m_Vao(model.m_Vao), m_Texture(textureId), m_VertexCount(model.m_VertexCount)
{

}

TexturedModel::TexturedModel()
    : m_Texture(0)
{

}

void TexturedModel::bind() const
{
    glBindVertexArray(m_Vao);
    bindTexture(0);
}

void TexturedModel::bindTexture(int index) const
{
    m_Texture.bindTexture(index);
}

void TexturedModel::unbind()
{
    Texture::unbindTexture();
}

size_t TexturedModel::vertexCount() const
{
    return m_VertexCount;
}

bool TexturedModel::operator==(const TexturedModel &rhs) const
{
    return m_Vao == rhs.m_Vao &&
           m_VertexCount == rhs.m_VertexCount &&
           m_Texture.textureId() == rhs.m_Texture.textureId();
}

GLuint TexturedModel::vaoID() const
{
    return m_Vao;
}

void TexturedModel::setVertexCount(int vertexCount)
{
    m_VertexCount = vertexCount;
}
