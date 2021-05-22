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
		static void drawComponent(entt::registry &, entt::entity)
		{}
	};

	template<>
	void ComponentTemplate::drawComponent<Transform3DComponent>(entt::registry &registry, entt::entity entity)
	{
		if (registry.has<Transform3DComponent>(entity))
		{
			Transform3DComponent &transform = registry.get<Transform3DComponent>(entity);
			if (ImGui::CollapsingHeader("Transform3D"))
			{
				ImGui::Columns(4);
				EditorUtil::drawTransform3DHeader();

				ImGui::Text("Position");
				EditorUtil::drawTransform3DRow(transform.position, "##PosX", "##PosY", "##PosZ");
				ImGui::Text("Rotation");
				EditorUtil::drawTransform3DRow(transform.rotation, "##RotX", "##RotY", "##RotZ");
				ImGui::Text("Scale");
				EditorUtil::drawTransform3DRow(transform.scale, "##ScX", "##ScY", "##ScZ");
			}
		}
	}

	template<>
	void ComponentTemplate::drawComponent<RenderComponent>(entt::registry &registry, entt::entity entity)
	{
		static FileChooser fileChooser{};
		static Model model;
		static Texture texture;

		static bool changed = true;

		if (registry.has<RenderComponent>(entity))
		{
			RenderComponent &component = registry.get<RenderComponent>(entity);
			if (ImGui::CollapsingHeader("Render"))
			{
				ImGui::Columns(2);
				EditorUtil::loadModel(fileChooser, model, changed);
				ImGui::NextColumn();
				EditorUtil::loadTexture(fileChooser, texture, changed);

				if (changed && texture.isValidTexture() && model.isValidModel())
				{
					component.texturedModel = TexturedModel(model, texture);
					changed = false;
				}
			}
		}
	}

	template<>
	void ComponentTemplate::drawComponent<RigidBodyComponent>(entt::registry &registry, entt::entity entity)
	{
		if (registry.has<RigidBodyComponent>(entity))
		{
			RigidBodyComponent &component = registry.get<RigidBodyComponent>(entity);
			if (ImGui::CollapsingHeader("Rigid body"))
			{
				ImGui::Checkbox("Transparent", &component.isTransparent);
			}
		}
	}
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
