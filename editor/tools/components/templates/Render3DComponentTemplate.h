//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_RENDER3DCOMPONENTTEMPLATE_H
#define SURVIVE_RENDER3DCOMPONENTTEMPLATE_H

#include <imgui.h>

#include "ComponentTemplate.h"
#include "OpenDialog.h"
#include "ObjParser.h"

namespace Survive
{
	template<>
	class ComponentTemplate<Render3DComponent>
	{
	private:
		OpenDialog m_OpenDialog;

		Loader m_Loader;
		DaeParser m_DaeParser;

		bool m_Changed = true;
		bool m_TextureDialogOpen = false;
		bool m_ModelDialogOpen = false;

	public:
		void drawComponent(Render3DComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Render3D", visible))
			{
				TexturedModel &texturedModel = component.texturedModel;

				ImGui::PushID("Render3D component");
				ImGui::Columns(2);

				loadModel(texturedModel.getModel(), component.modelName);
				ImGui::NextColumn();
				EditorUtil::loadTexture(m_OpenDialog, m_Loader, texturedModel.getTexture(), component.textureName,
										"Texture: %s", "Load texture", m_Changed, m_TextureDialogOpen);

				ImGui::Columns();
				ImGui::PopID();

				if (m_Changed && texturedModel.isValidTexture() && texturedModel.isValidModel())
				{
					m_Changed = false;
				}
			}
		}

	private:
		void loadModel(Model &model, std::string &modelName)
		{
			EditorUtil::showLoadedFile("Model: %s", modelName, "Load model", m_ModelDialogOpen);

			if (m_ModelDialogOpen)
			{
				m_OpenDialog.open(600.0f, 400.0f, &m_ModelDialogOpen);

				std::string selectedFilename = m_OpenDialog.getSelectedFilename();
				if (!m_ModelDialogOpen && !selectedFilename.empty())
				{
					std::optional<Model> loadedModel = getLoadedModel();

					if (loadedModel.has_value())
					{
						modelName = selectedFilename;
						model = Model(loadedModel.value());
						m_Changed = true;
					}
				}
			}
		}

		std::optional<Model> getLoadedModel()
		{
			std::string selectedFile;

			try
			{
				selectedFile = m_OpenDialog.getSelectedFile().string();
				Model model;

				if (selectedFile.ends_with("obj"))
				{
					model = ObjParser::loadObj(selectedFile, m_Loader);
				} else if (selectedFile.ends_with("dae"))
				{
					model = m_DaeParser.loadDae(selectedFile.c_str(), m_Loader);
				} else
				{
					Log::logMessage(LogType::ERROR, "Unknown file type");
				}

				return model.isValidModel() ? model : std::optional<Survive::Model>{};
			} catch (const std::exception &exception)
			{
				Log::logMessage(LogType::ERROR, "Could not load the model from " + selectedFile);
				return {};
			}
		}
	};
}

#endif //SURVIVE_RENDER3DCOMPONENTTEMPLATE_H