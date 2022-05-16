//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESHEETCOMPONENT_H
#define SURVIVE_SPRITESHEETCOMPONENT_H

namespace Survive
{
	struct SpriteSheetComponent
	{
	public:
		int row, col;
		int currentFrameIndex;
		bool animating;

		int spritesInSecond{};
		int endIndex{};
		int startIndex{};

		int numberOfEpochs = -1;

	private:
		double m_Time{};
		int m_CurrentEpoch{};
		int m_PreviousFrameIndex{};

	public:
		SpriteSheetComponent()
				: row(1), col(1), currentFrameIndex(0), animating(true)
		{}

		SpriteSheetComponent(int row, int col, int spritesInSecond, int numberOfEpochs = -1, int startRow = 0,
							 int startCol = 0)
				: row(row), col(col), animating(true), spritesInSecond(spritesInSecond),
				  numberOfEpochs(numberOfEpochs),
				  currentFrameIndex(startRow * col + startCol), endIndex(row * col - 1),
				  startIndex(currentFrameIndex)
		{}

		SpriteSheetComponent(int row, int col, int spritesInSecond, int startRow, int startCol,
							 int endRow, int endCol, int numberOfEpochs = -1)
				: row(row), col(col), animating(true), spritesInSecond(spritesInSecond),
				  numberOfEpochs(numberOfEpochs),
				  currentFrameIndex(startRow * col + startCol), endIndex(endRow * col + endCol),
				  startIndex(currentFrameIndex)
		{}

		SpriteSheetComponent(int row, int col, int spritesInSecond, int startIndex, int endIndex, int numberOfEpochs,
							 bool animate)
				: row(row), col(col), spritesInSecond(spritesInSecond), startIndex(startIndex), endIndex(endIndex),
				  numberOfEpochs(numberOfEpochs), animating(animate), currentFrameIndex(startIndex)
		{}

		friend class SpriteUpdate;
	};
}

#endif //SURVIVE_SPRITESHEETCOMPONENT_H
