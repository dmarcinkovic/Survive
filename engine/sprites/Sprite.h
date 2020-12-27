//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITE_H
#define SURVIVE_SPRITE_H

#include "../entity/Entity.h"
#include "../texture/TexturedModel.h"

class Sprite : public Entity
{
private:
	double m_Time{};

	int m_EndRow{}, m_EndCol{};
	int m_NumberOfEpochs{};
	int m_CurrentEpoch{};
	int m_PreviousFrameIndex{};

public:
	int m_CurrentFrameIndex{};
	const int m_Row, m_Col;
	bool m_Animate{};

	int m_SpritesInSecond{};

	Sprite(const TexturedModel &texture, const glm::vec3 &position, float scale, int row = 1, int col = 1);

	void animate(int spritesInSecond, int numberOfEpochs = -1, int startRow = 0, int startCol = 0);

	void animate(int spritesInSecond, int startRow, int startCol, int endRow, int endCol, int numberOfEpochs = -1);

	void drawSprite(int row, int col);

	void stopAnimation();

	void animate();

private:
	int calculateFrameIndex(int startIndex, int endIndex);
};


#endif //SURVIVE_SPRITE_H
