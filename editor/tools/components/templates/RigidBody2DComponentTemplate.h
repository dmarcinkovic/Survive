//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_RIGIDBODY2DCOMPONENTTEMPLATE_H
#define SURVIVE_RIGIDBODY2DCOMPONENTTEMPLATE_H

#include <imgui.h>
#include <box2d/box2d.h>

#include "ComponentTemplate.h"
#include "Components.h"
#include "EditorUtil.h"

namespace Survive
{
	template<>
	class ComponentTemplate<RigidBody2DComponent>
	{
	public:
		static void drawComponent(RigidBody2DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Rigid body 2D", visible))
			{
				static const char *bodyTypes[] = {"Static", "Kinematic", "Dynamic"};

				b2BodyDef &bodyDef = component.bodyDefinition;

				int currentItem = bodyDef.type;
				if (ImGui::Combo("Body type", &currentItem, bodyTypes, 3))
				{
					bodyDef.type = static_cast<b2BodyType>(currentItem);
				}

				ImGui::Separator();
				ImGui::Columns(2, nullptr, false);

				EditorUtil::drawColumnInputFloat("Linear drag", "##Linear drag", bodyDef.linearDamping, 0.0f);
				EditorUtil::drawColumnInputFloat("Angular drag", "##Angular drag", bodyDef.angularDamping, 0.0f);
				EditorUtil::drawColumnInputFloat("Gravity scale", "##Gravity scale", bodyDef.gravityScale);

				EditorUtil::drawColumnDragFloat2("Linear velocity", "##Linear velocity", bodyDef.linearVelocity);
				EditorUtil::drawColumnInputBool("Fixed angle", "##Fixed angle", bodyDef.fixedRotation);

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_RIGIDBODY2DCOMPONENTTEMPLATE_H
