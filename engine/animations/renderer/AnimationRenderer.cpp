//
// Created by david on 17. 05. 2020..
//
#include "AnimationRenderer.h"
#include "../../renderer/Renderer3DUtil.h"
#include "../../math/Maths.h"
#include "../../components/RenderComponent.h"
#include "../../components/Transform3DComponent.h"
#include "../../components/RigidBodyComponent.h"

AnimationRenderer::AnimationRenderer(const Light &light)
		: m_Light(light)
{
}

void AnimationRenderer::render(entt::registry &registry, const Camera &camera, const glm::vec4 &plane) const
{
	if (m_Objects.empty())
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_Shader);

	const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	m_Shader.loadViewMatrix(viewMatrix);
	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadPlane(plane);

	m_Shader.loadLight(m_Light.position(), m_Light.color());

	for (auto const&[texture, objects] : m_Objects)
	{
		Renderer3DUtil::prepareEntity(texture);
		renderScene(registry, objects, camera);

		Renderer3DUtil::finishRenderingEntity();
	}

	Renderer3DUtil::finishRendering();
}

void AnimationRenderer::addAnimatedModel(entt::registry &registry, entt::entity entity)
{
	RenderComponent renderComponent = registry.get<RenderComponent>(entity);
	auto &batch = m_Objects[renderComponent.texturedModel];

	batch.emplace_back(entity);
}

void
AnimationRenderer::renderScene(entt::registry &registry, const std::vector<entt::entity> &objects, const Camera &camera) const
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