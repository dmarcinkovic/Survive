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
			EditorUtil::drawTransform3DRow(component.scale, "##ScX", "##ScY", "##ScZ", 0.0f);

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

	template<>
	void ComponentTemplate::drawComponent(Transform2DComponent &component)
	{
		if (ImGui::CollapsingHeader("Transform2D"))
		{
			ImGui::Columns(3);
			EditorUtil::drawTransform2DHeader();

			ImGui::Text("Position");
			EditorUtil::drawTransform2DRow(component.position, "##PosX", "##PosY");
			ImGui::Text("Rotation");
			EditorUtil::drawTransform2DRow(component.rotation, "##RotX", "##RotY");
			ImGui::Text("Scale");
			EditorUtil::drawTransform2DRow(component.scale, "##ScX", "##ScY", 0.0f);

			ImGui::Columns();
		}
	}

	template<>
	void ComponentTemplate::drawComponent(ShadowComponent &component)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.65f, 0.6f, 0.6f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.5f, 0.55f, 0.5f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));

		if (ImGui::CollapsingHeader("Shadow"))
		{
			ImGui::Checkbox("Add shadow", &component.loadShadow);
		}

		ImGui::PopStyleColor(3);
	}

	template<>
	void ComponentTemplate::drawComponent(BloomComponent &component)
	{
		static FileChooser fileChooser;
		static bool changed = true;

		ImGui::Columns(2);
		if (ImGui::CollapsingHeader("Bloom"))
		{
			EditorUtil::loadTexture(fileChooser, component.emissiveTexture, component.textureName, changed);
		}

		ImGui::Columns();
	}
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
