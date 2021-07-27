//
// Created by david on 17. 05. 2020..
//


#include "ShadowComponent.h"
#include "AnimationRenderer.h"
#include "Maths.h"
#include "Renderer3DUtil.h"

Survive::AnimationRenderer::AnimationRenderer(const Light &light)
		: m_Light(light)
{
}

void Survive::AnimationRenderer::render(entt::registry &registry, const Camera &camera,
										GLuint shadowMap, const glm::vec4 &plane) const
{
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_Shader);
	loadUniforms(camera, shadowMap, plane);

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
		auto rotation = camera.m_Rotation + transform.rotation;

		glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
		m_Shader.loadTransformationMatrix(modelMatrix);

		const AnimationComponent &animationComponent = registry.get<AnimationComponent>(object);
		m_Shader.loadJointTransforms(getJointTransforms(animationComponent));

		if (registry.has<ShadowComponent>(object))
		{
			ShadowComponent shadowComponent = registry.get<ShadowComponent>(object);
			m_Shader.loadAddShadow(shadowComponent.loadShadow);
		} else
		{
			m_Shader.loadAddShadow(false);
		}

		const RenderComponent &renderComponent = registry.get<RenderComponent>(object);
		if (!renderComponent.texturedModel.getTexture().isValidTexture() && registry.has<SpriteComponent>(object))
		{
			const SpriteComponent &spriteComponent = registry.get<SpriteComponent>(object);
			m_Shader.loadColor(spriteComponent.color);
		}

		const RigidBodyComponent &rigidBody = registry.get<RigidBodyComponent>(object);
		Renderer3DUtil::addTransparency(!rigidBody.isTransparent, !rigidBody.isTransparent);


		glDrawArrays(GL_TRIANGLES, 0, renderComponent.texturedModel.vertexCount());

		Renderer3DUtil::addTransparency(rigidBody.isTransparent, rigidBody.isTransparent);
	}
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::AnimationRenderer::prepareEntities(entt::registry &registry)
{
	const auto &view = registry.view<RenderComponent, Transform3DComponent, RigidBodyComponent, AnimationComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : view)
	{
		const RenderComponent &renderComponent = view.get<RenderComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void Survive::AnimationRenderer::loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const
{
	const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	const glm::mat4 lightViewMatrix = Maths::createLightViewMatrix(m_Light);

	m_Shader.loadViewMatrix(viewMatrix);
	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadPlane(plane);
	m_Shader.loadLightProjectionMatrix(Maths::lightProjectionMatrix);
	m_Shader.loadLightViewMatrix(lightViewMatrix);

	m_Shader.loadLight(m_Light.position(), m_Light.color(), 0.7f, 3);

	Texture texture(shadowMap);
	texture.bindTexture(1);

	m_Shader.loadCameraPosition(camera.m_Position);
}

std::vector<glm::mat4>
Survive::AnimationRenderer::getJointTransforms(const AnimationComponent &animationComponent) const
{
	std::vector<glm::mat4> jointMatrices(animationComponent.numberOfJoints);
	addJointsToArray(animationComponent.rootJoint, jointMatrices);
	return jointMatrices;
}

void Survive::AnimationRenderer::addJointsToArray(const Joint &headJoint, std::vector<glm::mat4> &jointMatrices) const
{
	jointMatrices[headJoint.index()] = headJoint.getAnimatedTransform();
	for (auto const &childJoint : headJoint.children())
	{
		addJointsToArray(childJoint, jointMatrices);
	}
}
