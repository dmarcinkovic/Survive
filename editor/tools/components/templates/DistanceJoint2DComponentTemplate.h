
//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_DISTANCEJOINT2DCOMPONENTTEMPLATE_H
#define SURVIVE_DISTANCEJOINT2DCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "Joint2DComponentTemplate.h"
#include "Components.h"
#include "ComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<DistanceJoint2DComponent> : public Joint2DComponentTemplate
	{
	public:
		static void drawComponent(DistanceJoint2DComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Distance joint 2D", visible))
			{
				ImGui::Columns(2, nullptr, false);

				b2DistanceJointDef &jointDef = component.jointDef;

				drawJoint2DProperties("##DistanceBody", component.connectedBodyName, component.connectedBody,
									  jointDef.localAnchorA, jointDef.localAnchorB, jointDef.collideConnected);

				ImGui::Separator();

				EditorUtil::drawColumnDragFloat("Min length", "##DistanceJointMinLen", jointDef.minLength);
				EditorUtil::drawColumnDragFloat("Max length", "##DistanceJointMaxLen", jointDef.maxLength);

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_DISTANCEJOINT2DCOMPONENTTEMPLATE_H
