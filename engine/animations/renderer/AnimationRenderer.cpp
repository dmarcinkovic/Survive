//
// Created by david on 17. 05. 2020..
//
#include "AnimationRenderer.h"
#include "../../renderer/Renderer3DUtil.h"
#include "../../math/Maths.h"
#include "../../components/RenderComponent.h"
#include "../../components/Transform3DComponent.h"
#include "../../components/RigidBodyComponent.h"
#include "../../components/AnimationComponent.h"

AnimationRenderer::AnimationRenderer(const Light &light)
		: m_Light(light)
{
}

void AnimationRenderer::render(entt::registry &registry, const Camera &camera, const glm::vec4 &plane) const
{
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_Shader);

	const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	m_Shader.loadViewMatrix(viewMatrix);
	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadPlane(plane);

	m_Shader.loadLight(m_Light.position(), m_Light.color());

	for (auto const&[texture, objects] : entities)
	{
		Renderer3DUtil::prepareEntity(texture);
		renderScene(registry, objects, camera);

		Renderer3DUtil::finishRenderingEntity();
	}

	Renderer3DUtil::finishRendering();
}

void
AnimationRenderer::renderScene(entt::registry &registry, const std::vector<entt::entity> &objects,
							   const Camera &camera) const
{
	for (auto const &object : objects)
	{
		Transform3DComponent transform = registry.get<Transform3DComponent>(object);
		auto rotation = camera.m_Rotation + transform.rotation;

		glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
		m_Shader.loadTransformationMatrix(modelMatrix);

		RigidBodyComponent rigidBody = registry.get<RigidBodyComponent>(object);
		Renderer3DUtil::addTransparency(!rigidBody.isTransparent, !rigidBody.isTransparent);

		RenderComponent renderComponent = registry.get<RenderComponent>(object);
		glDrawArrays(GL_TRIANGLES, 0, renderComponent.texturedModel.vertexCount());

		Renderer3DUtil::addTransparency(rigidBody.isTransparent, rigidBody.isTransparent);
	}
}

std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
AnimationRenderer::prepareEntities(entt::registry &registry)
{
	auto view = registry.view<RenderComponent, Transform3DComponent, RigidBodyComponent, AnimationComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : view)
	{
		RenderComponent renderComponent = view.get<RenderComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}
