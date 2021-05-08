//
// Created by david on 03. 03. 2021..
//

#include "SpriteUpdate.h"
#include "Display.h"

void Survive::SpriteUpdate::update(entt::registry &registry)
{
	registry.view<SpriteSheetComponent>().each([](SpriteSheetComponent &sprite) {
		if (sprite.animating)
		{
			updateSprite(sprite);
		}
	});
}

void Survive::SpriteUpdate::updateSprite(SpriteSheetComponent &sprite)
{
	int epochs = sprite.m_NumberOfEpochs;
	int startIndex = sprite.m_StartIndex;

	int endRow = sprite.m_EndRow;
	int endCol = sprite.m_EndCol;

	int frameIndex = calcFrameIndex(sprite, startIndex, endRow * sprite.col + endCol);
	if (epochs == -1)
	{
		sprite.currentFrameIndex = startIndex + frameIndex;
	} else if (sprite.m_CurrentEpoch < epochs)
	{
		const static int size = sprite.row * sprite.col;
		sprite.currentFrameIndex = startIndex + frameIndex;

		if (sprite.m_PreviousFrameIndex != sprite.currentFrameIndex &&
			(sprite.currentFrameIndex + 1) % size == startIndex)
		{
			++sprite.m_CurrentEpoch;
		}

		sprite.m_PreviousFrameIndex = sprite.currentFrameIndex;
	}
}

int Survive::SpriteUpdate::calcFrameIndex(SpriteSheetComponent &sprite, int startIndex, int endIndex)
{
	sprite.m_Time += Display::getFrameTime() * sprite.m_SpritesInSecond;
	sprite.m_Time = std::fmod(sprite.m_Time, endIndex - startIndex + 1);

	return std::floor(sprite.m_Time);
}
