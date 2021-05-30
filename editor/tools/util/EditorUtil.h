//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_EDITORUTIL_H
#define SURVIVE_EDITORUTIL_H

#include <string>
#include <glm/vec3.hpp>

#include "FileChooser.h"
#include "Loader.h"

namespace Survive
{
	class EditorUtil
	{
	public:
		static void setStyleColors();

		static void resetStyleColors();

		static void drawTransform3DHeader();

		static void drawTransform3DRow(glm::vec3 &vec, const char *x, const char *y, const char *z,
									   float lowerBound = std::numeric_limits<float>::lowest());

		static void loadModel(FileChooser &fileChooser, Model &model, std::string &modelName, bool &changed);

		static void loadTexture(FileChooser &fileChooser, Texture &texture, std::string &textureName, bool &changed);

	private:
		static void setDragFloat(float &value, const char *label, const ImVec4 &frameBg, const ImVec4 &increment,
								 float lowerBound = std::numeric_limits<float>::min());

		static ImVec4 add(const ImVec4 &vec1, const ImVec4 &vec2);

		static std::optional<Model> getLoadedModel(const FileChooser &fileChooser, Loader &loader);

		static std::optional<Texture> getLoadedTexture(const FileChooser &fileChooser);

		static void showRenderComponent(const char *format,
										const std::string &name, const char *label, bool &load);
	};
}

#endif //SURVIVE_EDITORUTIL_H
