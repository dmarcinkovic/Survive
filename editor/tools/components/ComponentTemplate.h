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
		static FileChooser fileChooser{};
		static Model model;
		static Texture texture;

		static bool changed = true;

		if (ImGui::CollapsingHeader("Render"))
		{
			ImGui::Columns(2);
			EditorUtil::loadModel(fileChooser, model, changed);
			ImGui::NextColumn();
			EditorUtil::loadTexture(fileChooser, texture, changed);

			if (changed && texture.isValidTexture() && model.isValidModel())
			{
				std::cout << "Created textured model\n";
				TexturedModel texturedModel(model, texture);
				changed = false;
			}
		}
	}
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
