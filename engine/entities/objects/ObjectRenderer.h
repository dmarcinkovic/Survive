//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECTRENDERER_H
#define SURVIVE_OBJECTRENDERER_H

#include <unordered_map>
#include <functional>

#include "entt.hpp"
#include "ObjectShader.h"
#include "Camera.h"
#include "Light.h"
#include "TexturedModel.h"
#include "Renderer3D.h"

namespace Survive
{
	class ObjectRenderer : public Renderer3D
	{
	private:
		ObjectShader m_Shader;

		Texture m_DefaultTexture{};
		entt::entity m_SkyBox = entt::null;

	protected:
		const Light &m_Light;

	public:
		explicit ObjectRenderer(const Light &light);

		void render(entt::registry &registry, const Camera &camera, GLuint shadowMap,
					const glm::vec4 &plane = glm::vec4{}) const;

		void addSkybox(entt::entity skybox);

	protected:
		static void drawOutline(const entt::registry &registry, entt::entity entity);

		static void renderBloom(const entt::registry &registry, entt::entity entity, const ObjectShader &shader);

		void renderReflection(entt::registry &registry, entt::entity entity, const ObjectShader &shader) const;

		void renderRefraction(entt::registry &registry, entt::entity entity, const ObjectShader &shader) const;

		void renderMaterial(const entt::registry &registry, entt::entity entity, const ObjectShader &shader) const;

		static bool getTransparencyProperty(const entt::registry &registry, entt::entity object);

	private:
		void renderScene(entt::registry &registry,
						 const std::vector<entt::entity> &objects, const Camera &camera) const;

		void loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const;

		void loadObjectUniforms(entt::registry &registry, entt::entity,
								const Texture &texture, const Camera &camera) const;

		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);
	};
}

#endif //SURVIVE_OBJECTRENDERER_H
