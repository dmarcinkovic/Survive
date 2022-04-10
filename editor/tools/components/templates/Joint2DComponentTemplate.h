//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_JOINT2DCOMPONENTTEMPLATE_H
#define SURVIVE_JOINT2DCOMPONENTTEMPLATE_H

#include <imgui.h>
#include <box2d/box2d.h>

#include "entt.hpp"
#include "EditorUtil.h"
#include "Log.h"

namespace Survive
{
	class Joint2DComponentTemplate
	{
	private:
		static void initializeDragDropTarget(entt::entity &connectedBody, std::string &name)
		{
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("Joint2D"))
				{
					auto *data = reinterpret_cast<std::tuple<int, int, const char *> *>(payload->Data);

					int bodyA = std::get<0>(*data);
					int bodyB = std::get<1>(*data);

					if (bodyA == bodyB)
					{
						Log::logMessage(LogType::ERROR, "Body A should not be equal to body B");
					} else
					{
						connectedBody = static_cast<entt::entity>(bodyB);
						name = std::get<2>(*data);
					}
				}

				ImGui::EndDragDropTarget();
			}
		}

	protected:
		static void
		drawJoint2DProperties(const char *label, std::string &connectedBodyName, entt::entity &connectedBody,
							  b2Vec2 &anchorA, b2Vec2 &anchorB, bool &collideConnected)
		{
			EditorUtil::drawColumnInputText(label, "Connected Rigid Body", connectedBodyName);
			initializeDragDropTarget(connectedBody, connectedBodyName);

			ImGui::NextColumn();

			EditorUtil::drawColumnDragFloat2("Anchor", "##DistanceAnchorA", anchorA);
			EditorUtil::drawColumnDragFloat2("Connected anchor", "##DistanceAnchorB", anchorB);
			EditorUtil::drawColumnInputBool("Collide connected", "##DistanceCollide", collideConnected);
		}
	};
}

#endif //SURVIVE_JOINT2DCOMPONENTTEMPLATE_H
