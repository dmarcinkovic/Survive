//
// Created by david on 10. 04. 2022..
//

#ifndef SURVIVE_RIGIDBODY3DCOMPONENTTEMPLATE_H
#define SURVIVE_RIGIDBODY3DCOMPONENTTEMPLATE_H

#include "Components.h"
#include "ComponentTemplate.h"
#include "EditorUtil.h"

namespace Survive
{
	template<>
	class ComponentTemplate<RigidBody3DComponent>
	{
	private:
		static constexpr float max = std::numeric_limits<float>::max();

	public:
		static void drawComponent(RigidBody3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Rigid body 3D", visible))
			{
				static const char *bodyTypes[] = {"Static", "Kinematic", "Dynamic"};

				auto currentItem = static_cast<int>(component.bodyType);
				if (ImGui::Combo("Body type", &currentItem, bodyTypes, 3))
				{
					component.bodyType = static_cast<rp3d::BodyType>(currentItem);
				}

				ImGui::Separator();

				ImGui::Columns(2, nullptr, false);

				EditorUtil::drawColumnDragFloat("Mass", "##3D Body mass", component.mass, 0, max);
				EditorUtil::drawColumnInputFloat("Angular drag", "##3D drag", component.angularDrag);
				EditorUtil::drawColumnInputFloat("Linear damping", "##3D linear damping", component.linearDamping);
				EditorUtil::drawColumnInputBool("Use gravity", "##3D use gravity", component.useGravity);

				EditorUtil::drawColumnDragFloat3("Linear velocity", "##3D Linear velocity", component.linearVelocity);

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_RIGIDBODY3DCOMPONENTTEMPLATE_H
