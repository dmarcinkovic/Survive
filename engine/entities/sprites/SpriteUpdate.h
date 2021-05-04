//
// Created by david on 03. 03. 2021..
//

#ifndef SURVIVE_SPRITEUPDATE_H
#define SURVIVE_SPRITEUPDATE_H


#include "SpritesRenderer.h"

namespace Survive
{
	class SpriteUpdate
	{
	public:
		static void update(entt::registry &registry);

	private:
		static void updateSprite(SpriteSheetComponent &sprite);

		static int calcFrameIndex(SpriteSheetComponent &sprite, int startIndex, int endIndex);
	};
}

#endif //SURVIVE_SPRITEUPDATE_H
