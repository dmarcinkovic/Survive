//
// Created by david on 14.06.22..
//

#ifndef SURVIVE_SKYBOXCOMPONENTTEMPLATE_H
#define SURVIVE_SKYBOXCOMPONENTTEMPLATE_H

#include <array>

#include "ComponentTemplate.h"
#include "SkyboxComponent.h"
#include "OpenDialog.h"
#include "Constants.h"
#include "EditorUtil.h"

namespace Survive
{
	template<>
	class ComponentTemplate<SkyboxComponent>
	{
	private:
		static constexpr std::array FACE_NAMES{"right", "left", "top", "bottom", "front", "back"};

		OpenDialog m_OpenDialog;
		Loader m_Loader;
		std::array<bool, Constants::NUMBER_OF_FACES> m_Open{};

	public:
		void drawComponent(SkyboxComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Skybox", visible))
			{
				ImGui::Columns(2);
				for (int i = 0; i < Constants::NUMBER_OF_FACES; ++i)
				{
					const std::string id = "Skybox component " + std::to_string(i);
					ImGui::PushID(id.c_str());

					loadFace(component, i);
					ImGui::NextColumn();

					ImGui::PopID();
				}

				ImGui::Columns();

				loadCubeMap(component);
			}
		}

	private:
		void loadFace(SkyboxComponent &component, int index)
		{
			std::string face(FACE_NAMES[index]);
			std::string format = "Face " + face + ": %s";
			const std::string &name = component.faces[index];
			std::string label = "Load " + face + " face";

			EditorUtil::showLoadedFile(format.c_str(), name, label.c_str(), m_Open[index]);

			if (m_Open[index])
			{
				m_OpenDialog.open(600.0f, 400.0f, &m_Open[index]);
				std::string selectedFilename = m_OpenDialog.getSelectedFilename();
				if (!m_Open[index] && !selectedFilename.empty())
				{
					component.faces[index] = m_OpenDialog.getSelectedFile().string();
					component.m_ModelLoaded = false;
					component.m_LoadedTextures[index] = true;
				}
			}
		}

		void loadCubeMap(SkyboxComponent &component)
		{
			const std::vector<std::string> &faces = component.faces;

			if (!component.m_ModelLoaded && component.m_LoadedTextures.all())
			{
				try
				{
					Texture cubeMap = m_Loader.loadCubeMap(component.faces);
					Model model = m_Loader.renderCube();
					component.skyboxModel = TexturedModel(model, cubeMap);
					component.m_ModelLoaded = true;
				} catch (const std::runtime_error &error)
				{}
			}
		}
	};
}

#endif //SURVIVE_SKYBOXCOMPONENTTEMPLATE_H
