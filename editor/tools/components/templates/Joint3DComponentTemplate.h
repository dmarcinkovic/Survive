//
// Created by david on 26.04.22..
//

#ifndef SURVIVE_JOINT3DCOMPONENTTEMPLATE_H
#define SURVIVE_JOINT3DCOMPONENTTEMPLATE_H

#include "JointComponentTemplate.h"
#include "EditorUtil.h"
#include "JointComponent.h"

namespace Survive
{
	class Joint3DComponentTemplate : public JointComponentTemplate
	{
	protected:
		static void drawConnectedBodyUI(JointComponent &component)
		{
			std::string &connectedBodyName = component.connectedBodyName;
			EditorUtil::drawColumnInputText("##Hinge3DJoint", "Connected Rigid Body", connectedBodyName);
			initializeDragDropTarget(component.connectedBody, connectedBodyName);

			ImGui::NextColumn();
		}
	};
}

#endif //SURVIVE_JOINT3DCOMPONENTTEMPLATE_H
