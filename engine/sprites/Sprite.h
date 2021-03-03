//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITE_H
#define SURVIVE_SPRITE_H

#include "../texture/TexturedModel.h"

struct Sprite
{
private:
	double m_Time{};

	int m_EndRow{}, m_EndCol{};
	int m_NumberOfEpochs{};
	int m_CurrentEpoch{};
	int m_PreviousFrameIndex{};

	int m_CurrentFrameIndex{};
	int m_SpritesInSecond{};

public:
	int row, col;

	Sprite();

	Sprite(int row, int col, int spritesInSecond, int numberOfEpochs = -1, int startRow = 0, int startCol = 0);

	Sprite(int row, int col, int spritesInSecond, int startRow, int startCol, int endRow, int endCol, int numberOfEpochs = -1);

	void update();

	[[nodiscard]] int getFrameIndex() const;

private:
	int calculateFrameIndex(int startIndex, int endIndex);
};


#endif //SURVIVE_SPRITE_H
