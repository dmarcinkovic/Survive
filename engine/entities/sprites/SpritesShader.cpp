//
// Created by david on 29. 03. 2020..
//

#include "SpritesShader.h"

Survive::SpritesShader::SpritesShader()
		: Shader(VERTEX_FILE, FRAGMENT_FILE)
{
	getUniformLocations();
}

void Survive::SpritesShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::SpritesShader::getUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationCol = glGetUniformLocation(m_Program, "col");
	m_LocationRow = glGetUniformLocation(m_Program, "row");
	m_LocationSpriteIndex = glGetUniformLocation(m_Program, "spriteIndex");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
}

void Survive::SpritesShader::loadSpriteSize(int row, int col) const
{
	loadInteger(m_LocationRow, row);
	loadInteger(m_LocationCol, col);
}

void Survive::SpritesShader::loadSpritePosition(int currentIndex) const
{
	loadInteger(m_LocationSpriteIndex, currentIndex);
}

void Survive::SpritesShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}
