//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_COMPONENTTEMPLATE_H
#define SURVIVE_COMPONENTTEMPLATE_H

#include <imgui.h>

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

			ImGui::Columns();
		}
	}

	template<>
	void ComponentTemplate::drawComponent(RenderComponent &component)
	{
		static FileChooser fileChooser{};
		static bool changed = true;

		if (ImGui::CollapsingHeader("Render"))
		{
			TexturedModel &texturedModel = component.texturedModel;

			ImGui::Columns(2);
			EditorUtil::loadModel(fileChooser, texturedModel.getModel(), component.modelName, changed);
			ImGui::NextColumn();
			EditorUtil::loadTexture(fileChooser, texturedModel.getTexture(), component.textureName, changed);

			if (changed && texturedModel.isValidTexture() && texturedModel.getModel().isValidModel())
			{
				changed = false;
			}

			ImGui::Columns();
		}
	}

	template<>
	void ComponentTemplate::drawComponent(RigidBodyComponent &component)
	{
		if (ImGui::CollapsingHeader("Rigid body"))
		{
			ImGui::Checkbox("Transparent", &component.isTransparent);
		}
	}
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
