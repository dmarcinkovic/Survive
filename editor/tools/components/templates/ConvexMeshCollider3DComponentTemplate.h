//
// Created by david on 12. 04. 2022..
//

#ifndef SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENTTEMPLATE_H
#define SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENTTEMPLATE_H

#include "ComponentTemplate.h"
#include "Collider3DComponentTemplate.h"
#include "Components.h"

namespace Survive
{
	template<>
	class ComponentTemplate<ConvexMeshCollider3DComponent> : public ComponentTemplate<Collider3DComponent>
	{
	public:
		static void drawComponent(ConvexMeshCollider3DComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("ConvexMesh collider 3D", visible))
			{
				ImGui::PushID("ConvexMesh3D");
				ComponentTemplate<Collider3DComponent>::drawComponent(component, nullptr);
				ImGui::PopID();

				ImGui::Columns(2, nullptr, false);

				EditorUtil::drawColumnInputInt("Number of vertices", "##MeshNVertices", component.numberOfVertices);
				EditorUtil::drawColumnInputInt("Number of faces", "##MeshFaces", component.numberOfFaces);

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_CONVEXMESHCOLLIDER3DCOMPONENTTEMPLATE_H
