//
// Created by david on 26.04.22..
//

#ifndef SURVIVE_CHARACTERJOINT3DCOMPONENTTEMPLATE_H
#define SURVIVE_CHARACTERJOINT3DCOMPONENTTEMPLATE_H

#include "Components.h"
#include "ComponentTemplate.h"
#include "Joint3DComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<CharacterJoint3DComponent> : public Joint3DComponentTemplate
	{
	public:
		static void drawComponent(CharacterJoint3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Character joint 3D", visible))
			{
				ImGui::Columns(2, nullptr, false);

				drawConnectedBodyUI(component);

				rp3d::BallAndSocketJointInfo &info = component.jointInfo;
				drawFirstBodyInfo(info);

				EditorUtil::drawColumnDragFloat3("Connected Body Anchor", "##CharacterCBodyAnchor",
												 info.anchorPointBody2LocalSpace);

				EditorUtil::drawColumnInputBool("Enable Collision", "##Character3DCollision", info.isCollisionEnabled);

				ImGui::Columns();
			}
		}

	private:
		static void drawFirstBodyInfo(rp3d::BallAndSocketJointInfo &info)
		{
			if (info.isUsingLocalSpaceAnchors)
			{
				EditorUtil::drawColumnDragFloat3("Local Anchor", "##LocalCharacterAnchor",
												 info.anchorPointBody1LocalSpace);
			} else
			{
				EditorUtil::drawColumnDragFloat3("Anchor", "##CharacterJAnchor", info.anchorPointWorldSpace);
			}

			EditorUtil::drawColumnInputBool("Use Local Space Anchors", "##Character3DUseLocal",
											info.isUsingLocalSpaceAnchors);
		}
	};
}

#endif //SURVIVE_CHARACTERJOINT3DCOMPONENTTEMPLATE_H
