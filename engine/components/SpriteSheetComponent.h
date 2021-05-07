//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESHEETCOMPONENT_H
#define SURVIVE_SPRITESHEETCOMPONENT_H

#include "../texture/TexturedModel.h"

namespace Survive
{
	struct SpriteSheetComponent
	{
	public:
		int row, col;
		int currentFrameIndex;
		bool animating;

	private:
		double m_Time{};

		int m_EndRow{}, m_EndCol{};
		int m_NumberOfEpochs{};
		int m_CurrentEpoch{};
		int m_PreviousFrameIndex{};

		int m_SpritesInSecond{};
		int m_StartIndex{};

	public:
		SpriteSheetComponent()
				: row(1), col(1), currentFrameIndex(0), animating(true)
		{}

		SpriteSheetComponent(int row, int col, int spritesInSecond, int numberOfEpochs = -1, int startRow = 0,
							 int startCol = 0)
				: row(row), col(col), animating(true), m_SpritesInSecond(spritesInSecond),
				  m_NumberOfEpochs(numberOfEpochs),
				  currentFrameIndex(startRow * col + startCol), m_EndRow(row - 1), m_EndCol(col - 1),
				  m_StartIndex(currentFrameIndex)
		{}

		SpriteSheetComponent(int row, int col, int spritesInSecond, int startRow, int startCol,
							 int endRow, int endCol,
							 int numberOfEpochs = -1)
				: row(row), col(col), animating(true), m_SpritesInSecond(spritesInSecond),
				  m_NumberOfEpochs(numberOfEpochs),
				  currentFrameIndex(startRow * col + startCol), m_EndRow(endRow), m_EndCol(endCol),
				  m_StartIndex(currentFrameIndex)
		{}

		friend class SpriteUpdate;
	};
}

#endif //SURVIVE_SPRITESHEETCOMPONENT_H
