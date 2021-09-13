//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXT_H
#define SURVIVE_TEXT_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Font.h"
#include "TexturedModel.h"

namespace Survive
{
	class Text
	{
	private:
		constexpr static float PADDING = -15.0f;

		std::string m_Text;
		Font m_Font;
		bool m_Centered{};

		glm::vec3 m_BorderColor{};
		float m_BorderWidth{};
		bool m_AddBorder{};

		TexturedModel m_Model;

		std::vector<float> m_Vertices;
		std::vector<float> m_TextureCoordinates;

		float m_LineSpacing = 1.0f;

	public:
		friend class ComponentTemplate;

		Text(std::string text, Font font);

		Text();

		void loadTexture(Loader &loader);

		void centerText();

		const glm::vec3 &getBorderColor() const;

		float getBorderWidth() const;

		void addBorder(float borderWidth, const glm::vec3 &borderColor);

		void setText(std::string newText, Loader &loader);

		const TexturedModel &getModel() const;

		void setFont(const Font &font);

	private:
		void calculateTextureVertices();

		Model calculateVertices(Loader &loader);

		void addVertices(const Character &character, float cursorX, float cursorY);

		void alignText();

		std::pair<float, float> minMax() const;
	};
}

#endif //SURVIVE_TEXT_H
