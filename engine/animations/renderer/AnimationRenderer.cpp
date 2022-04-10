//
// Created by david on 17. 05. 2020..
//


#include "AnimationRenderer.h"
#include "Maths.h"
#include "Renderer3D.h"
#include "ShadowComponent.h"

Survive::AnimationRenderer::AnimationRenderer(const Light &light)
		: ObjectRenderer(light)
{
}

void Survive::AnimationRenderer::renderAnimation(entt::registry &registry, const Camera &camera,
												 GLuint shadowMap, const glm::vec4 &plane) const
{
	constexpr int numberOfVaoUnits = 6;

	auto entities = prepareEntities(registry);

	if (entities.empty())
	{
		return;
	}

	prepareRendering(m_Shader);
	glEnable(GL_STENCIL_TEST);
	loadUniforms(camera, shadowMap, plane);

	for (auto const &[texture, objects]: entities)
	{
		prepareEntity(texture, numberOfVaoUnits);
		renderScene(registry, objects, camera);

		finishRenderingEntity(numberOfVaoUnits);
	}

	finishRendering();
	glDisable(GL_STENCIL_TEST);
}

void Survive::AnimationRenderer::renderScene(entt::registry &registry, const std::vector<entt::entity> &objects,
											 const Camera &camera) const
{
	for (auto const &object: objects)
	{
		const Render3DComponent &renderComponent = registry.get<Render3DComponent>(object);
		loadObjectUniforms(registry, object, renderComponent.texturedModel.getTexture(), camera);
		drawOutline(registry, object);

		bool isTransparent = getTransparencyProperty(registry, object);
		addTransparency(!isTransparent, !isTransparent);

		glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
		addTransparency(isTransparent, isTransparent);

		Texture::unbindTexture();
	}
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::AnimationRenderer::prepareEntities(entt::registry &registry)
{
	const auto &view = registry.view<Render3DComponent, Transform3DComponent, AnimationComponent, TagComponent>();

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity: view)
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

	m_Shader.loadLightProjection(camera.getLightProjectionMatrix());
	m_Shader.loadLightViewMatrix(m_Light.getViewMatrix());

	m_Shader.loadLight(m_Light.position(), m_Light.color(), 0.7f, 3);

	Texture texture(shadowMap);
	texture.bindTexture(1);

	m_Shader.loadCameraPosition(camera.position);
}

void Survive::AnimationRenderer::loadObjectUniforms(entt::registry &registry, entt::entity entity,
													const Texture &texture, const Camera &camera) const
{
	const Transform3DComponent &transform = registry.get<Transform3DComponent>(entity);
	glm::vec3 rotation = camera.rotation + transform.rotation;

	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
	m_Shader.loadTransformationMatrix(modelMatrix);
	m_Shader.loadTextures();

	if (registry.any_of<ShadowComponent>(entity))
	{
		ShadowComponent shadowComponent = registry.get<ShadowComponent>(entity);
		m_Shader.loadAddShadow(shadowComponent.loadShadow);
	} else
	{
		m_Shader.loadAddShadow(false);
	}

	const AnimationComponent &animationComponent = registry.get<AnimationComponent>(entity);
	m_Shader.loadJointTransforms(animationComponent.jointTransforms);

	renderMaterial(registry, entity, m_Shader);

	renderReflection(registry, entity, m_Shader);
	renderRefraction(registry, entity, m_Shader);
	renderBloom(registry, entity, m_Shader);
}
