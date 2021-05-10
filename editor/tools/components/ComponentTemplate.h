//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_COMPONENTTEMPLATE_H
#define SURVIVE_COMPONENTTEMPLATE_H

#include <imgui.h>
#include <iostream>

#include "ObjParser.h"
#include "Components.h"
#include "EditorUtil.h"
#include "FileChooser.h"
#include "Loader.h"

namespace Survive
{
	class ComponentTemplate
	{
	public:
		template<typename ComponentType>
		static void drawComponent(ComponentType &component)
		{}
	};

	template<>
	void ComponentTemplate::drawComponent(Transform3DComponent &component)
	{
		if (ImGui::CollapsingHeader("Transform3D"))
		{
			ImGui::Columns(4);
			EditorUtil::drawTransform3DHeader();

			ImGui::Text("Position");
			EditorUtil::drawTransform3DRow(component.position, "##PosX", "##PosY", "##PosZ");
			ImGui::Text("Rotation");
			EditorUtil::drawTransform3DRow(component.rotation, "##RotX", "##RotY", "##RotZ");
			ImGui::Text("Scale");
			EditorUtil::drawTransform3DRow(component.scale, "##ScX", "##ScY", "##ScZ");
		}
	}

	template<>
	void ComponentTemplate::drawComponent(RenderComponent &component)
	{
		static bool loadModel = false;
		static bool loadTexture = false;
		static FileChooser fileChooser{};
		static Loader loader;
		static std::string loadedModel;
		static std::string loadedTexture;

		if (ImGui::CollapsingHeader("Render"))
		{
			ImGui::Columns(2);
			ImGui::Text("Model: %s", loadedModel.c_str());
			ImGui::NextColumn();
			if (ImGui::Button("Load model"))
			{
				loadModel = true;
			}

			ImGui::NextColumn();
			ImGui::Text("Texture: %s", loadedTexture.c_str());
			ImGui::NextColumn();
			if (ImGui::Button("Load texture"))
			{
				loadTexture = true;
			}

			if (loadModel)
			{
				fileChooser.open(600.0f, 400.0f, &loadModel);
				if (!loadModel)
				{
					try
					{
						std::string selectedFile = fileChooser.getSelectedFile();
						std::cout << "Selected file: " << selectedFile << '\n';
						if (!selectedFile.empty())
						{
							Model model = ObjParser::loadObj(selectedFile.c_str(), loader);
							loadedModel = fileChooser.getSelectedFilename();
						}
					} catch(const std::exception &ignorable)
					{
						std::cout << "Caught an exception\n";
						// TODO Log
					}
				}
			}

			if (loadTexture)
			{
				fileChooser.open(600.0f, 400.0f, &loadTexture);
				if (!loadTexture)
				{
					std::string selectedFile = fileChooser.getSelectedFile();
					if (!selectedFile.empty())
					{
						Texture texture = Loader::loadTexture(selectedFile.c_str());
						if (texture.isValidTexture())
						{
							loadedTexture = fileChooser.getSelectedFilename();
						}
					}
				}
			}
		}
	}
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
