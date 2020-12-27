//
// Created by david on 29. 03. 2020..
//

#include "SpritesShader.h"

SpritesShader::SpritesShader()
		: Shader(VERTEX_FILE, FRAGMENT_FILE)
{
	getUniformLocations();
}

void SpritesShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void SpritesShader::getUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationCol = glGetUniformLocation(m_Program, "col");
	m_LocationRow = glGetUniformLocation(m_Program, "row");
	m_LocationSpriteIndex = glGetUniformLocation(m_Program, "spriteIndex");
}

void SpritesShader::loadSpriteSize(int row, int col) const
{
	loadInteger(m_LocationRow, row);
	loadInteger(m_LocationCol, col);
}

void SpritesShader::loadSpritePosition(int currentIndex) const
{
	loadInteger(m_LocationSpriteIndex, currentIndex);
}
