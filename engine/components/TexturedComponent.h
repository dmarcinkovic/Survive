//
// Created by david on 06. 03. 2021..
//

#ifndef SURVIVE_TEXTUREDCOMPONENT_H
#define SURVIVE_TEXTUREDCOMPONENT_H


namespace Survive
{
	struct TexturedComponent
	{
		std::vector<Texture> textures{};

		TexturedComponent() = default;

		explicit TexturedComponent(std::vector<Texture> textures)
				: textures(std::move(textures))
		{}
	};
}

#endif //SURVIVE_TEXTUREDCOMPONENT_H
