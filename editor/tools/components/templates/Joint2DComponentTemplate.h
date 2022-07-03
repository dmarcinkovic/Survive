//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_JOINT2DCOMPONENTTEMPLATE_H
#define SURVIVE_JOINT2DCOMPONENTTEMPLATE_H

#include <imgui.h>
#include <box2d/box2d.h>
#include <entt.hpp>

#include "JointComponentTemplate.h"
#include "EditorUtil.h"
#include "Log.h"

namespace Survive
{
	class Joint2DComponentTemplate : public JointComponentTemplate
	{
	protected:
		static void
		drawJoint2DProperties(const char *label, std::string &connectedBodyName, entt::entity &connectedBody,
							  b2Vec2 &anchorA, b2Vec2 &anchorB, bool &collideConnected)
		{
			EditorUtil::drawColumnInputText(label, "Connected Rigid Body", connectedBodyName);
			initializeDragDropTarget(connectedBody, connectedBodyName);

			ImGui::NextColumn();

			std::string id = std::string(label) + "Anchors";
			ImGui::PushID(id.c_str());

			EditorUtil::drawColumnDragFloat2("Anchor", "##AnchorA", anchorA);
			EditorUtil::drawColumnDragFloat2("Connected anchor", "##AnchorB", anchorB);
			EditorUtil::drawColumnInputBool("Collide connected", "##Collide", collideConnected);

			ImGui::PopID();
		}
	};
}

#endif //SURVIVE_JOINT2DCOMPONENTTEMPLATE_H
