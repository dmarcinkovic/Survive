//
// Created by david on 09. 05. 2021..
//

#ifndef SURVIVE_COMPONENTTEMPLATE_H
#define SURVIVE_COMPONENTTEMPLATE_H

#include <imgui.h>

#include "ObjParser.h"
#include "Components.h"
#include "EditorUtil.h"
#include "FileChooser.h"
#include "Loader.h"

namespace Survive
{
	class ComponentTemplate
	{
	public:
		template<typename ComponentType>
		static void drawComponent(ComponentType &component, bool* = nullptr)
		{}
	};

	template<>
	void ComponentTemplate::drawComponent(Transform3DComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Transform3D", visible))
		{
			ImGui::Columns(4);
			EditorUtil::drawTransform3DHeader();

			ImGui::Text("Position");
			EditorUtil::drawTransform3DRow(component.position, "##PosX", "##PosY", "##PosZ");
			ImGui::Text("Rotation");
			EditorUtil::drawTransform3DRow(component.rotation, "##RotX", "##RotY", "##RotZ");
			ImGui::Text("Scale");
			EditorUtil::drawTransform3DRow(component.scale, "##ScX", "##ScY", "##ScZ", 0.0f);

			ImGui::Columns();
		}
	}

	template<>
	void ComponentTemplate::drawComponent(Render3DComponent &component, bool *visible)
	{
		static FileChooser fileChooser{};
		static bool changed = true;

		if (ImGui::CollapsingHeader("Render3D", visible))
		{
			TexturedModel &texturedModel = component.texturedModel;

			ImGui::Columns(2);
			EditorUtil::loadModel(fileChooser, texturedModel.getModel(), component.modelName, changed);
			ImGui::NextColumn();
			EditorUtil::loadTexture(fileChooser, texturedModel.getTexture(), component.textureName, changed);

			if (changed && texturedModel.isValidTexture() && texturedModel.isValidModel())
			{
				changed = false;
			}

			ImGui::Columns();
		}
	}

	template<>
	void ComponentTemplate::drawComponent(RigidBodyComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Rigid body", visible))
		{
			ImGui::Checkbox("Transparent", &component.isTransparent);
		}
	}

	template<>
	void ComponentTemplate::drawComponent(ShadowComponent &component, bool *visible)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.65f, 0.6f, 0.6f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.5f, 0.55f, 0.5f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));

		if (ImGui::CollapsingHeader("Shadow", visible))
		{
			ImGui::Checkbox("Add shadow", &component.loadShadow);
		}

		ImGui::PopStyleColor(3);
	}

	template<>
	void ComponentTemplate::drawComponent(BloomComponent &component, bool *visible)
	{
		static FileChooser fileChooser;
		static bool changed = true;

		if (ImGui::CollapsingHeader("Bloom", visible))
		{
			ImGui::Columns(2);
			EditorUtil::loadTexture(fileChooser, component.emissiveTexture, component.textureName, changed);
			ImGui::Columns();

			EditorUtil::drawSlider("##Bloom strength", "Bloom strength", component.bloomStrength, 0.0f, 5.0f);
		}
	}

	template<>
	void ComponentTemplate::drawComponent(ReflectionComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Reflection", visible))
		{
			EditorUtil::drawSlider("##Reflection factor", "Reflection factor", component.reflectionFactor);
		}
	}

	template<>
	void ComponentTemplate::drawComponent(RefractionComponent &component, bool *visible)
	{
		if (ImGui::CollapsingHeader("Refraction", visible))
		{
			EditorUtil::drawSlider("##Refraction index", "Refraction index", component.refractiveIndex, 0.0f, 3.0f);
			EditorUtil::drawSlider("##Refraction factor", "Refraction factor", component.refractiveFactor);
		}
	}

	template<>
	void ComponentTemplate::drawComponent(Render2DComponent &component, bool *visible)
	{
		static FileChooser fileChooser{};
		static bool changed = true;
		static Loader loader;

		if (ImGui::CollapsingHeader("Render2D", visible))
		{
			TexturedModel &texturedModel = component.texturedModel;

			ImGui::Columns(2);
			EditorUtil::loadTexture(fileChooser, texturedModel.getTexture(), component.textureName, changed);
			EditorUtil::loadQuadModel(changed, texturedModel, loader);

			ImGui::Columns();
		}
	}
}

#endif //SURVIVE_COMPONENTTEMPLATE_H
