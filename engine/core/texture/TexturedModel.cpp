//
// Created by david on 24. 03. 2020..
//

#include "TexturedModel.h"

Survive::TexturedModel::TexturedModel(const Model &model, const Texture &texture)
		: m_Vao(model.m_Vao), m_Texture(texture), m_VertexCount(model.m_VertexCount)
{

}

Survive::TexturedModel::TexturedModel()
		: m_Texture(0)
{

}

void Survive::TexturedModel::bind() const
{
	glBindVertexArray(m_Vao);
	bindTexture(0);
}

void Survive::TexturedModel::bindTexture(int index) const
{
	m_Texture.bindTexture(index);
}

void Survive::TexturedModel::bindCubeTexture(int index) const
{
	m_Texture.bindCubeTexture(index);
}

void Survive::TexturedModel::unbind()
{
	Texture::unbindTexture();
}

void Survive::TexturedModel::unbindVao()
{
	glBindVertexArray(0);
}

GLsizei Survive::TexturedModel::vertexCount() const
{
	return m_VertexCount;
}

bool Survive::TexturedModel::operator==(const TexturedModel &rhs) const
{
	return m_Vao == rhs.m_Vao &&
		   m_VertexCount == rhs.m_VertexCount &&
		   m_Texture.textureId() == rhs.m_Texture.textureId();
}

GLuint Survive::TexturedModel::vaoID() const
{
	return m_Vao;
}

void Survive::TexturedModel::setVertexCount(int vertexCount)
{
	m_VertexCount = vertexCount;
}

bool Survive::TexturedModel::isValidTexture() const
{
	return m_Texture.textureId() != 0;
}

const Survive::Texture &Survive::TexturedModel::getTexture() const
{
	return m_Texture;
}
