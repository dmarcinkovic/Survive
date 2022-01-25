//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_EDITORUTIL_H
#define SURVIVE_EDITORUTIL_H

#include <string>
#include <glm/vec3.hpp>
#include <AL/al.h>
#include <box2d/box2d.h>

#include "entt.hpp"
#include "Renderer.h"
#include "DaeParser.h"
#include "AudioMaster.h"
#include "TexturedModel.h"
#include "OpenDialog.h"
#include "Loader.h"

namespace Survive
{
	class EditorUtil
	{
	private:
		DaeParser m_DaeParser;
		Loader m_Loader;

		bool m_LoadModel{};
		bool m_LoadTexture{};
		bool m_LoadSound{};

		int m_SelectedItem = -1;
		std::vector<Font> m_Fonts;

		std::vector<const char *> m_Items;
		std::vector<std::pair<const char *, const char *>> m_FontInfo;

		Texture m_FontIcon;
		Texture m_TextureIcon;

	public:
		EditorUtil();

		static void setStyleColors();

		static void resetStyleColors();

		static void drawTransform3DHeader();

		static void drawTransform3DRow(glm::vec3 &vec, const char *x, const char *y, const char *z,
									   float lowerBound = std::numeric_limits<float>::lowest());

		static void drawTransform2DHeader();

		void loadModel(OpenDialog &fileChooser, Model &model, std::string &modelName, bool &changed);

		void loadTexture(OpenDialog &fileChooser, Texture &texture, std::string &textureName,
						 const char *format, const char *label, bool &changed);

		static void loadQuadModel(bool &changed, TexturedModel &texturedModel, Loader &loader);

		void loadSound(OpenDialog &fileChooser, AudioMaster &audioMaster, ALint &sound,
					   std::string &soundFile, bool &changed);

		static void loadFont(OpenDialog &fileChooser, Font &font, bool &open, std::string &file);

		static void loadFontTextureAtlas(OpenDialog &fileChooser, Text &text, Font &font, Loader &loader, bool &open,
										 std::string &file);

		static void centerText(const std::string &text);

		void
		loadDraggedModels(entt::registry &registry, const std::filesystem::path &file, const Camera &camera,
						  float x, float y, float width, float height);

		static void registerListener(entt::registry &registry, Renderer &renderer,
									 const std::filesystem::path &file, Loader &loader);

		static bool drawTextInput(Text &text, std::string &string, Loader &loader);

		static void loadFontButton(const Texture &icon, const char *text, bool &open);

		static void loadFontBorder(bool &addBorder, float &borderWidth, glm::vec3 &borderColor);

		void chooseFont(OpenDialog &fileChooser, TextComponent &textComponent, Font &font);

		static void chooseFontSpacing(float &spacing, Text &text, Loader &loader);

		static void drawColumnInputInt(const char *text, const char *label, int &value);

		static void drawColumnInputBool(const char *text, const char *label, bool &value);

		static bool drawColumnInputFloat(const char *text, const char *label, float &value);

		static bool drawColumnDragFloat(const char *text, const char *label, float &value,
										float min, float max, float step = 1.0f);

		static bool drawColumnDragFloat2(const char *text, const char *label, b2Vec2 &value);

		static bool drawColumnDragFloat3(const char *text, const char *label, rp3d::Vector3 &value, float speed = 1.0f,
										 float min = 0.0f, float max = 0.0f);

		static void drawPolygonPoints(std::vector<b2Vec2> &points, b2PolygonShape &shape);

		static void addPolygonPoint(std::vector<b2Vec2> &points, b2PolygonShape &shape);

		static void moveBoxCenter(b2Vec2 *points, const b2Vec2 &diff);

		static bool disableButton(bool condition);

		static void enableButton(bool condition);

	private:
		static void setDragFloat(float &value, const char *label, const ImVec4 &frameBg, const ImVec4 &increment,
								 float lowerBound = std::numeric_limits<float>::min());

		static ImVec4 add(const ImVec4 &vec1, const ImVec4 &vec2);

		std::optional<Model> getLoadedModel(const OpenDialog &fileChooser);

		static void showLoadedFile(const char *format, const std::string &name, const char *label, bool &load);
	};
}

#endif //SURVIVE_EDITORUTIL_H
