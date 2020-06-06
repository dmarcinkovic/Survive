//
// Created by david on 24. 03. 2020..
//

#include "TexturedModel.h"

TexturedModel::TexturedModel(const Model &model, GLuint textureId)
        : m_Vao(model.m_Vao), m_TextureID(textureId), m_VertexCount(model.m_VertexCount)
{

}

void TexturedModel::bindTexture() const
{
    glBindVertexArray(m_Vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void TexturedModel::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

size_t TexturedModel::vertexCount() const
{
    return m_VertexCount;
}

bool TexturedModel::operator==(const TexturedModel &rhs) const
{
    return m_Vao == rhs.m_Vao &&
           m_VertexCount == rhs.m_VertexCount &&
           m_TextureID == rhs.m_TextureID;
}
