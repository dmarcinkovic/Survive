//
// Created by david on 17. 05. 2020..
//

#include "ObjectRenderer.h"
#include "../../components/Components.h"
#include "../../components/ShadowComponent.h"
#include "../../core/math/Maths.h"
#include "../../core/renderer/Renderer3DUtil.h"

Survive::ObjectRenderer::ObjectRenderer(const Light &light)
		: m_Light(light)
{
}

void
Survive::ObjectRenderer::render(entt::registry &registry, const Camera &camera, GLuint shadowMap,
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
Survive::ObjectRenderer::renderScene(const entt::registry &registry, const std::vector<entt::entity> &objects,
									 const Camera &camera) const
{
	for (auto const &object : objects)
	{
		loadObjectUniforms(registry, object, camera);
		drawOutline(registry, object);

		const RigidBodyComponent &rigidBody = registry.get<RigidBodyComponent>(object);
		Renderer3DUtil::addTransparency(!rigidBody.isTransparent, !rigidBody.isTransparent);

		const RenderComponent &renderComponent = registry.get<RenderComponent>(object);
		glDrawArrays(GL_TRIANGLES, 0, renderComponent.texturedModel.vertexCount());

		Renderer3DUtil::addTransparency(rigidBody.isTransparent, rigidBody.isTransparent);
		Texture::unbindTexture();
	}
}

void Survive::ObjectRenderer::loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const
{
	const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	const glm::mat4 lightViewMatrix = Maths::createLightViewMatrix(m_Light);
	m_Shader.loadLight(m_Light.position(), m_Light.color(), 0.7, 3);

	m_Shader.loadViewMatrix(viewMatrix);
	m_Shader.loadLightViewMatrix(lightViewMatrix);
	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadLightProjection(Maths::lightProjectionMatrix);
	m_Shader.loadPlane(plane);

	Texture texture(shadowMap);
	texture.bindTexture(1);

	m_Shader.loadCameraPosition(camera.position);
}

void Survive::ObjectRenderer::loadObjectUniforms(const entt::registry &registry, entt::entity entity,
												 const Camera &camera) const
{
	const Transform3DComponent &transform = registry.get<Transform3DComponent>(entity);
	glm::vec3 rotation = camera.rotation + transform.rotation;

	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
	m_Shader.loadTransformationMatrix(modelMatrix);
	m_Shader.loadTextures();

	ShadowComponent shadowComponent = registry.get<ShadowComponent>(entity);
	m_Shader.loadAddShadow(shadowComponent.loadShadow);

	renderReflectionAndRefraction(registry, entity);
	renderBloom(registry, entity);
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::ObjectRenderer::prepareEntities(entt::registry &registry)
{
	auto const &view = registry.view<RenderComponent, Transform3DComponent, RigidBodyComponent>(
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

void Survive::ObjectRenderer::drawOutline(const entt::registry &registry, entt::entity entity)
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

void Survive::ObjectRenderer::renderBloom(const entt::registry &registry, entt::entity entity) const
{
	if (registry.has<BloomComponent>(entity))
	{
		const BloomComponent &bloomComponent = registry.get<BloomComponent>(entity);

		bloomComponent.bloomTexture.bindTexture(3);
		m_Shader.loadBloomTexture(bloomComponent.bloomStrength);
		m_Shader.loadBloom(true);
	} else
	{
		m_Shader.loadBloom(false);

		static Texture bloomDefaultTexture(0);
		bloomDefaultTexture.bindTexture(3);
	}
}

void Survive::ObjectRenderer::renderReflectionAndRefraction(const entt::registry &registry, entt::entity entity) const
{
	static Texture defaultReflection(0);
	defaultReflection.bindTexture(2);

	if (registry.has<ReflectionComponent>(entity))
	{
		const ReflectionComponent &reflection = registry.get<ReflectionComponent>(entity);

		reflection.reflectionTexture.bindCubeTexture(2);
		m_Shader.loadReflectiveFactor(reflection.reflectionFactor);
	}

	if (registry.has<RefractionComponent>(entity))
	{
		const RefractionComponent &refraction = registry.get<RefractionComponent>(entity);

		refraction.refractionTexture.bindCubeTexture(2);
		m_Shader.loadRefractionData(refraction.refractiveIndex, refraction.refractiveFactor);
	}
}
