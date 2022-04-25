//
// Created by david on 22.04.22..
//

#ifndef SURVIVE_HINGEJOINT3DCOMPONENTTEMPLATE_H
#define SURVIVE_HINGEJOINT3DCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "Components.h"
#include "ComponentTemplate.h"
#include "JointComponentTemplate.h"

namespace Survive
{
	template<>
	class ComponentTemplate<HingeJoint3DComponent> : public JointComponentTemplate
	{
	public:
		static void drawComponent(HingeJoint3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Hinge joint 3D", visible))
			{
				ImGui::Columns(2, nullptr, false);

				drawConnectedBodyUI(component);

				rp3d::HingeJointInfo &jointInfo = component.jointInfo;

				drawFirstBodyInfo(jointInfo);
				drawSecondBodyInfo(jointInfo);

				drawMotorProperties(jointInfo);
				drawLimitProperties(jointInfo);

				EditorUtil::drawColumnInputBool("Enable Collision", "##Hinge3DCollision", jointInfo.isCollisionEnabled);

				ImGui::Columns();
			}
		}

	private:
		static void drawConnectedBodyUI(HingeJoint3DComponent &component)
		{
			std::string &connectedBodyName = component.connectedBodyName;
			EditorUtil::drawColumnInputText("##Hinge3DJoint", "Connected Rigid Body", connectedBodyName);
			initializeDragDropTarget(component.connectedBody, connectedBodyName);

			ImGui::NextColumn();
		}

		static void drawFirstBodyInfo(rp3d::HingeJointInfo &jointInfo)
		{
			if (jointInfo.isUsingLocalSpaceAnchors)
			{
				EditorUtil::drawColumnDragFloat3("Local Anchor", "##Hinge3LocalAnchor",
												 jointInfo.anchorPointBody1LocalSpace);
				EditorUtil::drawColumnDragFloat3("Local Axis", "##Hinge3DLocalAxis", jointInfo.rotationAxisBody1Local);
			} else
			{
				EditorUtil::drawColumnDragFloat3("Anchor", "##Hinge3DAnchor", jointInfo.anchorPointWorldSpace);
				EditorUtil::drawColumnDragFloat3("Axis", "##Hinge3DAxis", jointInfo.rotationAxisWorld);
			}

			EditorUtil::drawColumnInputBool("Use Local Space Anchors", "##Hinge3DConfigure",
											jointInfo.isUsingLocalSpaceAnchors);
		}

		static void drawSecondBodyInfo(rp3d::HingeJointInfo &jointInfo)
		{
			EditorUtil::drawColumnDragFloat3("Connected Body Anchor", "##Hinge3DConnectedAnchor",
											 jointInfo.anchorPointBody2LocalSpace);
			EditorUtil::drawColumnDragFloat3("Connected Body Axis", "##Hinge3DConnectedAxis",
											 jointInfo.rotationAxisBody2Local);
		}

		static void drawMotorProperties(rp3d::HingeJointInfo &jointInfo)
		{
			static constexpr float minValue = std::numeric_limits<float>::lowest();

			ImGui::Separator();
			EditorUtil::drawColumnInputBool("Use Motor", "##Hinge3DMotor", jointInfo.isMotorEnabled);

			ImGui::Indent();

			EditorUtil::drawColumnDragFloat("Motor Speed", "##Hinge3DMotorSpeed", jointInfo.motorSpeed, minValue);
			EditorUtil::drawColumnDragFloat("Max Torque", "##Hinge3DTorque", jointInfo.maxMotorTorque);

			ImGui::Unindent();
		}

		static void drawLimitProperties(rp3d::HingeJointInfo &jointInfo)
		{
			static constexpr float minValue = std::numeric_limits<float>::lowest();

			ImGui::Separator();
			EditorUtil::drawColumnInputBool("Use Limits", "##Hinge3DLimits", jointInfo.isLimitEnabled);

			ImGui::Indent();

			float minAngle = glm::degrees(jointInfo.minAngleLimit);
			if (EditorUtil::drawColumnDragFloat("Min Angle", "##Hinge3DMinAngle", minAngle, -360, 0))
			{
				jointInfo.minAngleLimit = glm::radians(minAngle);
			}

			float maxAngle = glm::degrees(jointInfo.maxAngleLimit);
			if (EditorUtil::drawColumnDragFloat("Max Angle", "##Hinge3DMaxAngle", maxAngle, 0, 360))
			{
				jointInfo.maxAngleLimit = glm::radians(maxAngle);
			}

			ImGui::Unindent();
		}
	};
}

#endif //SURVIVE_HINGEJOINT3DCOMPONENTTEMPLATE_H
