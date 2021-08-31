//
// Created by david on 24. 03. 2020..
//

#include "TexturedModel.h"

Survive::TexturedModel::TexturedModel(const Model &model, const Texture &texture)
		: m_Model(model), m_Texture(texture)
{

}

Survive::TexturedModel::TexturedModel()
		: m_Texture(0)
{

}

void Survive::TexturedModel::bind() const
{
	glBindVertexArray(m_Model.m_Vao);
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

GLsizei Survive::TexturedModel::vertexCount() const
{
	return m_Model.m_VertexCount;
}

bool Survive::TexturedModel::operator==(const TexturedModel &rhs) const
{
	return m_Model.m_Vao == rhs.m_Model.m_Vao &&
		   m_Model.m_VertexCount == rhs.m_Model.m_VertexCount &&
		   m_Texture.textureId() == rhs.m_Texture.textureId();
}

GLuint Survive::TexturedModel::vaoID() const
{
	return m_Model.m_Vao;
}

void Survive::TexturedModel::setVertexCount(int vertexCount)
{
	m_Model.m_VertexCount = vertexCount;
}

bool Survive::TexturedModel::isValidTexture() const
{
	return m_Texture.isValidTexture();
}

const Survive::Texture &Survive::TexturedModel::getTexture() const
{
	return m_Texture;
}

Survive::Model &Survive::TexturedModel::getModel()
{
	return m_Model;
}

Survive::Texture &Survive::TexturedModel::getTexture()
{
	return m_Texture;
}

bool Survive::TexturedModel::isValidModel() const
{
	return m_Model.isValidModel();
}

void Survive::TexturedModel::setTexture(const Texture &texture)
{
	m_Texture = texture;
}
