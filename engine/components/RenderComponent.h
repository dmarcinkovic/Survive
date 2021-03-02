//
// Created by david on 02. 03. 2021..
//

#ifndef SURVIVE_RENDERCOMPONENT_H
#define SURVIVE_RENDERCOMPONENT_H

#include "../texture/TexturedModel.h"

struct RenderComponent
{
	TexturedModel texturedModel;

	RenderComponent() = default;

	explicit RenderComponent(const TexturedModel &texturedModel)
		: texturedModel(texturedModel) {}
};

#endif //SURVIVE_RENDERCOMPONENT_H
