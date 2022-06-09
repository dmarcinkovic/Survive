//
// Created by david on 09.06.22..
//

#ifndef SURVIVE_TERRAINCOMPONENTTEMPLATE_H
#define SURVIVE_TERRAINCOMPONENTTEMPLATE_H

#include "TerrainComponent.h"
#include "ComponentTemplate.h"
#include "OpenDialog.h"

namespace Survive
{
	template<>
	class ComponentTemplate<TerrainComponent>
	{
	private:
		OpenDialog m_OpenDialog;
		Loader m_Loader;

		bool m_Changed = true;
		bool m_TextureDialogOpen = false;
		bool m_ModelDialogOpen = false;

	public:
		void drawComponent(TerrainComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Terrain", visible))
			{

			}
		}
	};
}

#endif //SURVIVE_TERRAINCOMPONENTTEMPLATE_H
