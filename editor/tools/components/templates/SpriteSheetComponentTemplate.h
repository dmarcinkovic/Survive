//
// Created by david on 13. 03. 2022..
//

#ifndef SURVIVE_SPRITESHEETCOMPONENTTEMPLATE_H
#define SURVIVE_SPRITESHEETCOMPONENTTEMPLATE_H

namespace Survive
{
	template<>
	class ComponentTemplate<SpriteSheetComponent>
	{
	public:
		static void drawComponent(SpriteSheetComponent &component, bool *visible)
		{
			if (ImGui::CollapsingHeader("Sprite sheet", visible))
			{
				ImGui::Columns(2, nullptr, false);

				EditorUtil::drawColumnInputInt("Number of rows", "##Number of rows", component.row);
				EditorUtil::drawColumnInputInt("Number of columns", "##Number of columns", component.col);
				ImGui::Separator();
				EditorUtil::drawColumnInputInt("Start index", "##Start index", component.startIndex);
				EditorUtil::drawColumnInputInt("End index", "##End index", component.endIndex);
				ImGui::Separator();
				EditorUtil::drawColumnInputInt("Sprites in second", "##NSprites", component.spritesInSecond);
				EditorUtil::drawColumnInputInt("Number of epochs", "##NEpochs", component.numberOfEpochs);
				ImGui::Separator();

				EditorUtil::drawColumnInputBool("Animate", "##Animate sprites", component.animating);

				ImGui::Columns();
			}
		}
	};
}

#endif //SURVIVE_SPRITESHEETCOMPONENTTEMPLATE_H
