//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_SPRITECOMPONENTTEMPLATE_H
#define SURVIVE_SPRITECOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<SpriteComponent>
	{
	public:
		static void drawComponent(SpriteComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Sprite", visible))
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(component.color));
			}
		}
	};

}

#endif //SURVIVE_SPRITECOMPONENTTEMPLATE_H
