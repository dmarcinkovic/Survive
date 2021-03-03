//
// Created by david on 29. 03. 2020..
//

#include <cmath>

#include "SpriteSheetComponent.h"
#include "../display/Display.h"

SpriteSheetComponent::SpriteSheetComponent()
		: row(1), col(1)
{

}

SpriteSheetComponent::SpriteSheetComponent(int row, int col, int spritesInSecond, int numberOfEpochs, int startRow, int startCol)
		: row(row), col(col), m_SpritesInSecond(spritesInSecond), m_NumberOfEpochs(numberOfEpochs),
		  m_CurrentFrameIndex(startRow * col + startCol), m_EndRow(row - 1), m_EndCol(col - 1)
{

}

SpriteSheetComponent::SpriteSheetComponent(int row, int col, int spritesInSecond, int startRow, int startCol, int endRow, int endCol,
										   int numberOfEpochs)
		: row(row), col(col), m_SpritesInSecond(spritesInSecond), m_NumberOfEpochs(numberOfEpochs),
		  m_CurrentFrameIndex(startRow * col + startCol), m_EndRow(endRow), m_EndCol(endCol)
{

}

void SpriteSheetComponent::update()
{
	static int startIndex = m_CurrentFrameIndex;

	if (m_NumberOfEpochs == -1)
	{
		m_CurrentFrameIndex = startIndex + calculateFrameIndex(startIndex, m_EndRow * col + m_EndCol);
	} else if (m_CurrentEpoch < m_NumberOfEpochs)
	{
		const static int size = row * col;
		m_CurrentFrameIndex = startIndex + calculateFrameIndex(startIndex, m_EndRow * col + m_EndCol);

		if (m_PreviousFrameIndex != m_CurrentFrameIndex &&
			(m_CurrentFrameIndex + 1) % size == startIndex)
		{
			++m_CurrentEpoch;
		}
		m_PreviousFrameIndex = m_CurrentFrameIndex;
	}
}

int SpriteSheetComponent::calculateFrameIndex(int startIndex, int endIndex)
{
	m_Time += Display::getFrameTime() * m_SpritesInSecond;
	m_Time = std::fmod(m_Time, endIndex - startIndex + 1);

	return std::floor(m_Time);
}

int SpriteSheetComponent::getFrameIndex() const
{
	return m_CurrentFrameIndex;
}


