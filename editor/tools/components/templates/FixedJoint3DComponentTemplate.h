//
// Created by david on 27.04.22..
//

#ifndef SURVIVE_FIXEDJOINT3DCOMPONENTTEMPLATE_H
#define SURVIVE_FIXEDJOINT3DCOMPONENTTEMPLATE_H

#include "ComponentTemplate.h"
#include "Components.h"
#include "Joint3DComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<FixedJoint3DComponent> : public Joint3DComponentTemplate
	{
	public:
		static void drawComponent(FixedJoint3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Fixed joint 3D", visible))
			{
				ImGui::Columns(2, nullptr, false);

				drawConnectedBodyUI(component);

				rp3d::FixedJointInfo &info = component.jointInfo;

				drawFirstBodyInfo(info);

				EditorUtil::drawColumnDragFloat3("Connected Body Anchor", "##FixedCBodyAnchor",
												 info.anchorPointBody2LocalSpace);

				EditorUtil::drawColumnInputBool("Enable Collision", "##Fixed3DCollision", info.isCollisionEnabled);

				ImGui::Columns();
			}
		}

	private:
		static void drawFirstBodyInfo(rp3d::FixedJointInfo &jointInfo)
		{
			if (jointInfo.isUsingLocalSpaceAnchors)
			{
				EditorUtil::drawColumnDragFloat3("Local Anchor", "##LocalFixedAnchor",
												 jointInfo.anchorPointBody1LocalSpace);
			} else
			{
				EditorUtil::drawColumnDragFloat3("Anchor", "##FixedJAnchor", jointInfo.anchorPointWorldSpace);
			}

			EditorUtil::drawColumnInputBool("Use Local Space Anchors", "##Fixed3DUseLocal",
											jointInfo.isUsingLocalSpaceAnchors);
		}
	};
}

#endif //SURVIVE_FIXEDJOINT3DCOMPONENTTEMPLATE_H
