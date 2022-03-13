//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_HINGEJOINT2DCOMPONENTTEMPLATE_H
#define SURVIVE_HINGEJOINT2DCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "Joint2DComponentTemplate.h"
#include "Components.h"
#include "ComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<HingeJoint2DComponent> : public Joint2DComponentTemplate
	{
	public:
		static void drawComponent(HingeJoint2DComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Hinge joint 2D", visible))
			{
				ImGui::Columns(2, nullptr, false);

				b2RevoluteJointDef &jointDef = component.jointDef;

				drawJoint2DProperties("##HingeBody", component.connectedBodyName, component.connectedBody,
									  jointDef.localAnchorA, jointDef.localAnchorB, jointDef.collideConnected);

				ImGui::Separator();
				drawMotorProperties(component);

				ImGui::Separator();
				drawAngleProperties(component);

				ImGui::Columns();
			}
		}

	private:
		static void drawMotorProperties(HingeJoint2DComponent &component)
		{
			static constexpr float min = std::numeric_limits<float>::min();

			b2RevoluteJointDef &jointDef = component.jointDef;

			ImGui::TextUnformatted("Motor");
			ImGui::NextColumn();
			ImGui::NextColumn();

			ImGui::Indent();
			EditorUtil::drawColumnInputBool("Use motor", "##UseHingeMotor", jointDef.enableMotor);
			EditorUtil::drawColumnDragFloat("Motor speed", "##HingeMotorSpeed", jointDef.motorSpeed, min);
			EditorUtil::drawColumnDragFloat("Max motor force", "##HingeMForce", jointDef.maxMotorTorque);

			ImGui::Unindent();
		}

		static void drawAngleProperties(Survive::HingeJoint2DComponent &component)
		{
			b2RevoluteJointDef &jointDef = component.jointDef;

			ImGui::TextUnformatted("Angle limits");
			ImGui::NextColumn();
			ImGui::NextColumn();

			ImGui::Indent();
			EditorUtil::drawColumnInputBool("Use limits", "##UseHingeLimits", jointDef.enableLimit);

			float lowerAngle = glm::degrees(jointDef.lowerAngle);
			if (EditorUtil::drawColumnDragFloat("Lower angle", "##HingeLAngle", lowerAngle, -359, 359))
			{
				jointDef.lowerAngle = glm::radians(lowerAngle);
			}

			float upperAngle = glm::degrees(jointDef.upperAngle);
			if (EditorUtil::drawColumnDragFloat("Upper angle", "##HingeUAngle", upperAngle, -359, 359))
			{
				jointDef.upperAngle = glm::radians(upperAngle);
			}

			ImGui::Unindent();
		}
	};
}

#endif //SURVIVE_HINGEJOINT2DCOMPONENTTEMPLATE_H
