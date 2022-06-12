//
// Created by david on 09.06.22..
//

#ifndef SURVIVE_TERRAINCOMPONENTTEMPLATE_H
#define SURVIVE_TERRAINCOMPONENTTEMPLATE_H

#include <array>

#include "TerrainComponent.h"
#include "ComponentTemplate.h"
#include "OpenDialog.h"
#include "EditorUtil.h"
#include "TerrainGenerator.h"

namespace Survive
{
	template<>
	class ComponentTemplate<TerrainComponent>
	{
	private:
		OpenDialog m_OpenDialog;
		Loader m_Loader;

		bool m_Changed = true;
		bool m_HeightMapDialogOpen = false;
		bool m_BlendMapDialogOpen = false;

		std::array<bool, 4> m_TexturesOpen{};

	public:
		void drawComponent(TerrainComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Terrain", visible))
			{
				ImGui::Columns(2);

				loadHeightMap(component);
				ImGui::NextColumn();

				ImGui::PushID("Terrain component blend map");
				EditorUtil::loadTexture(m_OpenDialog, m_Loader, component.terrainModel.getTexture(),
										component.blendMapPath, "Blend map: %s", "Load blend map", m_Changed,
										m_BlendMapDialogOpen);
				ImGui::NextColumn();
				ImGui::PopID();
				ImGui::Columns();

				ImGui::Separator();
				loadTextures(component);
			}
		}

	private:
		void loadHeightMap(TerrainComponent &component)
		{
			ImGui::PushID("Terrain component height map");
			EditorUtil::showLoadedFile("Height map: %s", component.heightMapPath, "Load height map",
									   m_HeightMapDialogOpen);
			if (m_HeightMapDialogOpen)
			{
				m_OpenDialog.open(600.0f, 400.0f, &m_HeightMapDialogOpen);
				std::string selectedFilename = m_OpenDialog.getSelectedFilename();
				if (!m_HeightMapDialogOpen && !selectedFilename.empty())
				{
					Model terrainModel = TerrainGenerator::generateTerrain(m_Loader, selectedFilename.c_str());
					if (terrainModel.isValidModel())
					{
						component.terrainModel.getModel() = terrainModel;
						component.heightMapPath = selectedFilename;
					}
				}
			}
			ImGui::PopID();
		}

		void loadTextures(TerrainComponent &component)
		{
			ImGui::Columns(2);
			ImGui::PushID("Terrain component textures");

			for (int i = 0; i < component.textures.size(); ++i)
			{
				Texture &texture = component.textures[i];
				std::string &texturePath = component.texturePaths[i];

				ImGui::PushID(i);
				std::string format = "Texture " + std::to_string(i + 1) + ": %s";
				std::string label = "Load texture " + std::to_string(i + 1);
				EditorUtil::loadTexture(m_OpenDialog, m_Loader, texture, texturePath, format.c_str(), label.c_str(),
										m_Changed, m_TexturesOpen[i]);
				ImGui::NextColumn();
				ImGui::PopID();
			}

			ImGui::PopID();
			ImGui::Columns();
		}
	};
}

#endif //SURVIVE_TERRAINCOMPONENTTEMPLATE_H
