//
// Created by david on 22.04.22..
//

#ifndef SURVIVE_JOINTCOMPONENTTEMPLATE_H
#define SURVIVE_JOINTCOMPONENTTEMPLATE_H

#include <imgui.h>
#include <tuple>

#include "entt.hpp"
#include "Log.h"

namespace Survive
{
	class JointComponentTemplate
	{
	protected:
		static void initializeDragDropTarget(entt::entity &connectedBody, std::string &name)
		{
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("Joint"))
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
	};
}

#endif //SURVIVE_JOINTCOMPONENTTEMPLATE_H
