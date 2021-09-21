//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_FONT_H
#define SURVIVE_FONT_H

#include <unordered_map>

#include "Character.h"
#include "Texture.h"
#include "Loader.h"

namespace Survive
{
	class Font
	{
	private:
		std::unordered_map<int, Character> m_Characters;
		Texture m_FontTexture{};

		bool m_Loaded{};

		float m_Height{};
		float m_ScaleHeight{};

	public:
		explicit Font(const char *textureAtlas);

		Font() = default;

		void loadFontFromFntFile(const char *fntFile);

		void loadFontFromJsonFile(const char *jsonFile);

		const Character &getCharacter(int ascii) const;

		const Texture &getTexture() const;

		void setTexture(const Texture &fontTexture);

		[[nodiscard]] bool isFontLoaded() const;

		[[nodiscard]] bool isFontTextureValid() const;

		float getHeight() const;

		float getScaleHeight() const;
	};
}

#endif //SURVIVE_FONT_H
