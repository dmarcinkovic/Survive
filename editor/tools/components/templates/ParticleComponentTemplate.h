//
// Created by david on 30.05.22..
//

#ifndef SURVIVE_PARTICLECOMPONENTTEMPLATE_H
#define SURVIVE_PARTICLECOMPONENTTEMPLATE_H

#include <limits>

#include "Components.h"
#include "ComponentTemplate.h"
#include "EditorUtil.h"
#include "Constants.h"

namespace Survive
{
	template<>
	class ComponentTemplate<ParticleComponent>
	{
	private:
		OpenDialog m_OpenDialog;
		Loader m_Loader;

		bool m_Changed = true;
		bool m_Open = false;

	public:
		void drawComponent(ParticleComponent &component, bool *visible)
		{
			ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::CollapsingHeader("Particle", visible))
			{
				ImGui::Columns(2, nullptr, false);

				loadTexture(component.m_Model, component.texturePath);
				loadModel(component);

				drawProperties(component);

				ImGui::Columns();
			}
		}

	private:
		void loadTexture(TexturedModel &model, std::string &path)
		{
			ImGui::PushID("Particle component");
			EditorUtil::loadTexture(m_OpenDialog, m_Loader, model.getTexture(), path, "Particle Texture: %s",
									"Load texture", m_Changed, m_Open);
			ImGui::PopID();
			ImGui::NextColumn();
			ImGui::Separator();
		}

		void loadModel(ParticleComponent &component)
		{
			TexturedModel &model = component.m_Model;

			if (!model.isValidModel())
			{
				model.getModel() = m_Loader.renderQuad();
				component.m_Vbo = m_Loader.createEmptyVBO(ParticleRenderer::getVertexCount());
				addInstancedAttributes(model.vaoID(), component.m_Vbo);
			}
		}

		static void addInstancedAttributes(GLuint vao, GLuint vbo)
		{
			constexpr int instancedDataLength = Constants::PARTICLE_DATA_LENGTH;

			Loader::addInstancedAttribute(vao, vbo, 1, 4, instancedDataLength, 0);
			Loader::addInstancedAttribute(vao, vbo, 2, 4, instancedDataLength, 4);
			Loader::addInstancedAttribute(vao, vbo, 3, 4, instancedDataLength, 8);
			Loader::addInstancedAttribute(vao, vbo, 4, 4, instancedDataLength, 12);
			Loader::addInstancedAttribute(vao, vbo, 5, 1, instancedDataLength, 16);
		}

		static void drawProperties(ParticleComponent &component)
		{
			constexpr float lowestFloat = std::numeric_limits<float>::lowest();

			EditorUtil::drawColumnInputFloat("Particle Per Second", "##PPS", component.particlesPerSecond);
			EditorUtil::drawColumnInputFloat("Speed", "##ParticleSpeed", component.speed);
			EditorUtil::drawColumnInputFloat("Gravity", "##ParticleGravity", component.gravity, lowestFloat);
			EditorUtil::drawColumnInputFloat("Life Length", "##ParticleLifeLength", component.lifeLength);

			ImGui::Separator();

			EditorUtil::drawColumnDragFloat("Speed Error", "##ParticleSpeedError", component.speedError);
			EditorUtil::drawColumnDragFloat("Life Error", "##ParticleLifeError", component.lifeError);
			EditorUtil::drawColumnDragFloat("Scale Error", "##ParticleScaleErrro", component.scaleError);
			EditorUtil::drawColumnDragFloat("Direction Deviation", "##ParticleDirD", component.directionDeviation);

			ImGui::Separator();

			EditorUtil::drawColumnInputBool("Use Additive Blending", "##ParticleBlend",
											component.useAdditiveBlending);
		}
	};
}

#endif //SURVIVE_PARTICLECOMPONENTTEMPLATE_H
