//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_RENDER2DCOMPONENTTEMPLATE_H
#define SURVIVE_RENDER2DCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<Render2DComponent>
	{
	private:
		OpenDialog m_OpenDialog{};
		Loader m_Loader{};

		bool m_Changed = true;
		bool m_Open = false;

	public:
		void drawComponent(Render2DComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Render2D", visible))
			{
				TexturedModel &texturedModel = component.texturedModel;

				ImGui::PushID("Render 2D Component");
				ImGui::Columns(2);
				EditorUtil::loadTexture(m_OpenDialog, m_Loader, texturedModel.getTexture(), component.textureName,
										"Texture: %s", "Load texture", m_Changed, m_Open);
				loadQuadModel(texturedModel);

				ImGui::Columns();
				ImGui::PopID();
			}
		}

	private:
		void loadQuadModel(TexturedModel &texturedModel)
		{
			if (!texturedModel.isValidModel())
			{
				texturedModel.getModel() = m_Loader.renderQuad();
			}
		}
	};
}

#endif //SURVIVE_RENDER2DCOMPONENTTEMPLATE_H
