//
// Created by david on 17. 05. 2020..
//

#include "ObjectRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"
#include "../components/Components.h"

ObjectRenderer::ObjectRenderer(const Light &light)
		: m_Light(light)
{
}

void
ObjectRenderer::render(entt::registry &registry, const Camera &camera, GLuint shadowMap,
					   const glm::vec4 &plane) const
{
	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_Shader);
	glEnable(GL_STENCIL_TEST);

	loadUniforms(camera, shadowMap, plane);

	for (auto const&[texturedModel, objects] : entities)
	{
		Renderer3DUtil::prepareEntity(texturedModel);
		renderScene(registry, objects, camera);

		Renderer3DUtil::finishRenderingEntity();
	}

	Renderer3DUtil::finishRendering();
	glDisable(GL_STENCIL_TEST);
}

void
ObjectRenderer::renderScene(const entt::registry &registry, const std::vector<entt::entity> &objects,
							const Camera &camera) const
{
	for (auto const &object : objects)
	{
		loadObjectUniforms(registry, object, camera);
		drawOutline(registry, object);

		RigidBodyComponent rigidBody = registry.get<RigidBodyComponent>(object);
		Renderer3DUtil::addTransparency(!rigidBody.isTransparent, !rigidBody.isTransparent);

		RenderComponent renderComponent = registry.get<RenderComponent>(object);
		glDrawArrays(GL_TRIANGLES, 0, renderComponent.texturedModel.vertexCount());

		Renderer3DUtil::addTransparency(rigidBody.isTransparent, rigidBody.isTransparent);
		Texture::unbindCubeTexture();
	}
}

void ObjectRenderer::loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const
{
	const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	const glm::mat4 lightViewMatrix = Maths::createLightViewMatrix(m_Light);
	m_Shader.loadLight(m_Light.position(), m_Light.color(), 0.7, 3);

	m_Shader.loadAddShadow(shadowMap != 0);

	m_Shader.loadViewMatrix(viewMatrix);
	m_Shader.loadLightViewMatrix(lightViewMatrix);
	m_Shader.loadTextures();
	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadLightProjection(Maths::lightProjectionMatrix);
	m_Shader.loadPlane(plane);

	Texture texture(shadowMap);
	texture.bindTexture(1);

	m_Shader.loadCameraPosition(camera.m_Position);
}

void ObjectRenderer::loadObjectUniforms(const entt::registry &registry, entt::entity entity, const Camera &camera) const
{
	Transform3DComponent transform = registry.get<Transform3DComponent>(entity);
	glm::vec3 rotation = camera.m_Rotation + transform.rotation;

	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
	m_Shader.loadTransformationMatrix(modelMatrix);

	if (registry.has<ReflectionComponent>(entity))
	{
		ReflectionComponent reflection = registry.get<ReflectionComponent>(entity);

		reflection.reflectionTexture.bindCubeTexture(2);
		m_Shader.loadReflectiveFactor(reflection.reflectionFactor);
	}

	if (registry.has<RefractionComponent>(entity))
	{
		RefractionComponent refraction = registry.get<RefractionComponent>(entity);

		refraction.refractionTexture.bindCubeTexture(2);
		m_Shader.loadRefractionData(refraction.refractiveIndex, refraction.refractiveFactor);
	}

	if (registry.has<BloomComponent>(entity))
	{
		BloomComponent bloomComponent = registry.get<BloomComponent>(entity);

		bloomComponent.bloomTexture.bindTexture(3);
		m_Shader.loadBloom(bloomComponent.bloomStrength);
	}
}

std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
ObjectRenderer::prepareEntities(entt::registry &registry)
{
	auto view = registry.view<RenderComponent, Transform3DComponent, RigidBodyComponent>(
			entt::exclude<AnimationComponent>);

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity : view)
	{
		RenderComponent renderComponent = view.get<RenderComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void ObjectRenderer::drawOutline(const entt::registry &registry, entt::entity entity)
{
	if (registry.has<OutlineComponent>(entity))
	{
		const OutlineComponent &outline = registry.get<OutlineComponent>(entity);
		if (outline.drawOutline)
		{
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
		}
	} else
	{
		glStencilMask(0x00);
	}
}
