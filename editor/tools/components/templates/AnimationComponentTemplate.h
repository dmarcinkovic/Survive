//
// Created by david on 22.06.22..
//

#ifndef SURVIVE_ANIMATIONCOMPONENTTEMPLATE_H
#define SURVIVE_ANIMATIONCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "ComponentTemplate.h"
#include "AnimationComponent.h"
#include "EditorUtil.h"

namespace Survive
{
	template<>
	class ComponentTemplate<AnimationComponent>
	{
	public:
		void drawComponent(AnimationComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Animation", visible))
			{
				ImGui::Columns(2, nullptr, false);
				EditorUtil::drawColumnInputInt("Number of joints", "##AnimationNOJoints", component.numberOfJoints);
				ImGui::Columns();

				drawJoints(component);
			}
		}

	private:
		void drawJoints(AnimationComponent &component)
		{
			ImGui::TextUnformatted("Joints: ");
			ImGui::SameLine();
			float indent = ImGui::GetCursorPosX();

			ImGui::Indent(indent);
			drawJointHierarchy(component.rootJoint);
			ImGui::Unindent(indent);
		}

		void drawJointHierarchy(const Joint &joint)
		{
			ImGuiTreeNodeFlags flags = joint.children().empty() ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_None;
			if (ImGui::TreeNodeEx(joint.name().c_str(), flags))
			{
				for (auto const &childJoint: joint.children())
				{
					drawJointHierarchy(childJoint);
				}

				ImGui::TreePop();
			}
		}
	};
}

#endif //SURVIVE_ANIMATIONCOMPONENTTEMPLATE_H
