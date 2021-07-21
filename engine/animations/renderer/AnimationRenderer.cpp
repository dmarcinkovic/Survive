//
// Created by david on 17. 05. 2020..
//
#include "AnimationRenderer.h"
#include "Components.h"
#include "Maths.h"
#include "Renderer3DUtil.h"

Survive::AnimationRenderer::AnimationRenderer(const Light &light)
		: m_Light(light)
{
}

void Survive::AnimationRenderer::render(entt::registry &registry, const Camera &camera, const glm::vec4 &plane) const
{
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_Shader);
	loadUniforms(camera, plane);

	for (auto const&[texture, objects] : entities)
	{
		Renderer3DUtil::prepareEntity(texture);
		renderScene(registry, objects, camera);

		Renderer3DUtil::finishRenderingEntity();
	}

	Renderer3DUtil::finishRendering();
}

void
Survive::AnimationRenderer::renderScene(const entt::registry &registry, const std::vector<entt::entity> &objects,
										const Camera &camera) const
{
	for (auto const &object : objects)
	{
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(object);
		auto rotation = camera.rotation + transform.rotation;

		glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
		m_Shader.loadTransformationMatrix(modelMatrix);

		const RigidBodyComponent &rigidBody = registry.get<RigidBodyComponent>(object);
		Renderer3DUtil::addTransparency(!rigidBody.isTransparent, !rigidBody.isTransparent);

		const Render3DComponent &renderComponent = registry.get<Render3DComponent>(object);
		glDrawArrays(GL_TRIANGLES, 0, renderComponent.texturedModel.vertexCount());

		Renderer3DUtil::addTransparency(rigidBody.isTransparent, rigidBody.isTransparent);
	}
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::AnimationRenderer::prepareEntities(entt::registry &registry)
{
	const auto &view = registry.view<Render3DComponent, Transform3DComponent, RigidBodyComponent, AnimationComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : view)
	{
		const Render3DComponent &renderComponent = view.get<Render3DComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void Survive::AnimationRenderer::loadUniforms(const Camera &camera, const glm::vec4 &plane) const
{
	const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);

	m_Shader.loadViewMatrix(viewMatrix);
	m_Shader.loadProjectionMatrix(camera.getProjectionMatrix());
	m_Shader.loadPlane(plane);

	m_Shader.loadLight(m_Light.position(), m_Light.color());
}
