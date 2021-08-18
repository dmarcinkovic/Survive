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
	glEnable(GL_STENCIL_TEST);
	loadUniforms(camera, shadowMap, plane);

	for (auto const&[texture, objects] : entities)
	{
		Renderer3DUtil::prepareEntity(texture);
		renderScene(registry, objects, camera);

		Renderer3DUtil::finishRenderingEntity();
	}

	Renderer3DUtil::finishRendering();
	glDisable(GL_STENCIL_TEST);
}

void
Survive::AnimationRenderer::renderScene(const entt::registry &registry, const std::vector<entt::entity> &objects,
										const Camera &camera) const
{
	for (auto const &object : objects)
	{
		const Render3DComponent &renderComponent = registry.get<Render3DComponent>(object);
		loadObjectUniforms(registry, object, renderComponent.texturedModel.getTexture(), camera);
		drawOutline(registry, object);

		const RigidBodyComponent &rigidBody = registry.get<RigidBodyComponent>(object);
		Renderer3DUtil::addTransparency(!rigidBody.isTransparent, !rigidBody.isTransparent);

		glDrawArrays(GL_TRIANGLES, 0, renderComponent.texturedModel.vertexCount());

		Renderer3DUtil::addTransparency(rigidBody.isTransparent, rigidBody.isTransparent);
		Texture::unbindTexture();
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

void Survive::AnimationRenderer::loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const
{
	m_Shader.loadViewMatrix(camera.getViewMatrix());
	m_Shader.loadProjectionMatrix(camera.getProjectionMatrix());

	m_Shader.loadPlane(plane);

	m_Shader.loadLightProjectionMatrix(m_Light.getProjectionMatrix());
	m_Shader.loadLightViewMatrix(m_Light.getViewMatrix());

	m_Shader.loadLight(m_Light.position(), m_Light.color(), 0.7f, 3);

	Texture texture(shadowMap);
	texture.bindTexture(1);

	m_Shader.loadCameraPosition(camera.position);
}

void Survive::AnimationRenderer::loadObjectUniforms(const entt::registry &registry, entt::entity entity,
													const Texture &texture, const Camera &camera) const
{
	const Transform3DComponent &transform = registry.get<Transform3DComponent>(entity);
	auto rotation = camera.rotation + transform.rotation;

	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
	m_Shader.loadTransformationMatrix(modelMatrix);
	m_Shader.loadTextures();

	if (registry.has<ShadowComponent>(entity))
	{
		ShadowComponent shadowComponent = registry.get<ShadowComponent>(entity);
		m_Shader.loadAddShadow(shadowComponent.loadShadow);
	} else
	{
		m_Shader.loadAddShadow(false);
	}

	const AnimationComponent &animationComponent = registry.get<AnimationComponent>(entity);
	m_Shader.loadJointTransforms(animationComponent.jointTransforms);

	loadMaterial(registry, entity);

	renderBloom(registry, entity);
	renderReflectionAndRefraction(registry, entity);
}

void Survive::AnimationRenderer::renderBloom(const entt::registry &registry, entt::entity entity) const
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

void
Survive::AnimationRenderer::renderReflectionAndRefraction(const entt::registry &registry, entt::entity entity) const
{
	static Texture defaultReflection(0);
	defaultReflection.bindTexture(2);

	if (registry.has<ReflectionComponent>(entity))
	{
		const ReflectionComponent &reflection = registry.get<ReflectionComponent>(entity);
//		Render3DComponent &skybox = registry.get<Render3DComponent>(m_Skybox);

//		reflection.reflectionTexture.bindCubeTexture(2);
		m_Shader.loadReflectionFactor(reflection.reflectionFactor);
	} else
	{
		m_Shader.loadReflectionFactor(0.0f);
	}

	if (registry.has<RefractionComponent>(entity))
	{
		const RefractionComponent &refraction = registry.get<RefractionComponent>(entity);
//		Render3DComponent &skybox = registry.get<Render3DComponent>(m_Skybox);

//		refraction.refractionTexture.bindCubeTexture(2);
		m_Shader.loadRefractionData(refraction.refractiveIndex, refraction.refractiveFactor);
	} else
	{
		m_Shader.loadRefractionData(0.0f, 0.0f);
	}
}

void Survive::AnimationRenderer::drawOutline(const entt::registry &registry, entt::entity entity)
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

void Survive::AnimationRenderer::loadMaterial(const entt::registry &registry, entt::entity entity) const
{
	static glm::vec4 defaultColor{0, 0, 0, 0};
	if (registry.has<SpriteComponent>(entity))
	{
		const SpriteComponent &spriteComponent = registry.get<SpriteComponent>(entity);
		m_Shader.loadColor(spriteComponent.color);
	} else
	{
		m_Shader.loadColor(defaultColor);
	}
}
