//
// Created by david on 29. 03. 2020..
//

#include "SpriteSheetComponent.h"

SpriteSheetComponent::SpriteSheetComponent()
		: row(1), col(1), currentFrameIndex(0)
{

}

SpriteSheetComponent::SpriteSheetComponent(int row, int col, int spritesInSecond, int numberOfEpochs, int startRow,
										   int startCol)
		: row(row), col(col), m_SpritesInSecond(spritesInSecond), m_NumberOfEpochs(numberOfEpochs),
		  currentFrameIndex(startRow * col + startCol), m_EndRow(row - 1), m_EndCol(col - 1),
		  m_StartIndex(currentFrameIndex)
{

}

SpriteSheetComponent::SpriteSheetComponent(int row, int col, int spritesInSecond, int startRow, int startCol,
										   int endRow, int endCol,
										   int numberOfEpochs)
		: row(row), col(col), m_SpritesInSecond(spritesInSecond), m_NumberOfEpochs(numberOfEpochs),
		  currentFrameIndex(startRow * col + startCol), m_EndRow(endRow), m_EndCol(endCol),
		  m_StartIndex(currentFrameIndex)
{

}


