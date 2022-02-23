//
// Created by david on 17. 05. 2020..
//

#include "ObjectRenderer.h"
#include "Components.h"
#include "ShadowComponent.h"
#include "Maths.h"
#include "Renderer3D.h"

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

	Renderer3D::prepareRendering(m_Shader);
	glEnable(GL_STENCIL_TEST);
	loadUniforms(camera, shadowMap, plane);

	for (auto const&[texturedModel, objects]: entities)
	{
		Renderer3D::prepareEntity(texturedModel);
		renderScene(registry, objects, camera);

		Renderer3D::finishRenderingEntity();
	}

	Renderer3D::finishRendering();
	glDisable(GL_STENCIL_TEST);
}

void Survive::ObjectRenderer::renderScene(entt::registry &registry, const std::vector<entt::entity> &objects,
									 const Camera &camera) const
{
	for (auto const &object: objects)
	{
		const Render3DComponent &renderComponent = registry.get<Render3DComponent>(object);
		loadObjectUniforms(registry, object, renderComponent.texturedModel.getTexture(), camera);
		drawOutline(registry, object);

		bool isTransparent = getTransparencyProperty(registry, object);
		Renderer3D::addTransparency(!isTransparent, !isTransparent);

		glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);

		Renderer3D::addTransparency(isTransparent, isTransparent);
		Texture::unbindTexture();
		Texture::unbindCubeTexture();
	}
}

void Survive::ObjectRenderer::loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const
{
	m_Shader.loadLight(m_Light.position(), m_Light.color(), 0.7, 3);

	m_Shader.loadViewMatrix(camera.getViewMatrix());
	m_Shader.loadLightViewMatrix(m_Light.getViewMatrix());
	m_Shader.loadProjectionMatrix(camera.getProjectionMatrix());
	m_Shader.loadLightProjection(camera.getLightProjectionMatrix());
	m_Shader.loadPlane(plane);

	Texture texture(shadowMap);
	texture.bindTexture(1);

	m_Shader.loadCameraPosition(camera.position);
}

void Survive::ObjectRenderer::loadObjectUniforms(entt::registry &registry, entt::entity entity,
												 const Texture &texture, const Camera &camera) const
{
	const Transform3DComponent &transform = registry.get<Transform3DComponent>(entity);
	glm::vec3 rotation = camera.rotation + transform.rotation;

	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);
	m_Shader.loadTransformationMatrix(modelMatrix);
	m_Shader.loadTextures();

	if (registry.any_of<ShadowComponent>(entity))
	{
		const ShadowComponent &shadowComponent = registry.get<ShadowComponent>(entity);
		m_Shader.loadAddShadow(shadowComponent.loadShadow);
	} else
	{
		m_Shader.loadAddShadow(false);
	}

	renderMaterial(registry, entity, m_Shader);

	renderReflection(registry, entity, m_Shader);
	renderRefraction(registry, entity, m_Shader);
	renderBloom(registry, entity, m_Shader);
}

std::unordered_map<Survive::TexturedModel, std::vector<entt::entity>, Survive::TextureHash>
Survive::ObjectRenderer::prepareEntities(entt::registry &registry)
{
	auto const &view = registry.view<Render3DComponent, Transform3DComponent>(
			entt::exclude<AnimationComponent>);

	std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash> entities;
	for (auto const &entity: view)
	{
		Render3DComponent renderComponent = view.get<Render3DComponent>(entity);

		std::vector<entt::entity> &batch = entities[renderComponent.texturedModel];
		batch.emplace_back(entity);
	}

	return entities;
}

void Survive::ObjectRenderer::drawOutline(const entt::registry &registry, entt::entity entity)
{
	if (registry.any_of<OutlineComponent>(entity))
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

void Survive::ObjectRenderer::renderBloom(const entt::registry &registry, entt::entity entity,
										  const ObjectShader &shader)
{
	if (registry.any_of<BloomComponent>(entity))
	{
		const BloomComponent &bloomComponent = registry.get<BloomComponent>(entity);

		bloomComponent.bloomTexture.bindTexture(3);
		shader.loadBloomTexture(bloomComponent.bloomStrength);
		shader.loadBloom(true);
	} else
	{
		shader.loadBloom(false);

		static Texture bloomDefaultTexture(0);
		bloomDefaultTexture.bindTexture(3);
	}
}

void Survive::ObjectRenderer::renderReflection(entt::registry &registry, entt::entity entity,
											   const ObjectShader &shader) const
{
	m_DefaultTexture.bindTexture(2);

	if (registry.any_of<ReflectionComponent>(entity) && m_SkyBox != entt::null)
	{
		const ReflectionComponent &reflection = registry.get<ReflectionComponent>(entity);
		Render3DComponent &skybox = registry.get<Render3DComponent>(m_SkyBox);

		skybox.texturedModel.getTexture().bindCubeTexture(2);
		shader.loadReflectiveFactor(reflection.reflectionFactor);
	} else
	{
		shader.loadReflectiveFactor(0.0f);
	}
}

void Survive::ObjectRenderer::renderRefraction(entt::registry &registry, entt::entity entity,
											   const ObjectShader &shader) const
{
	m_DefaultTexture.bindTexture(2);

	if (registry.any_of<RefractionComponent>(entity) && m_SkyBox != entt::null)
	{
		const RefractionComponent &refraction = registry.get<RefractionComponent>(entity);
		Render3DComponent &skybox = registry.get<Render3DComponent>(m_SkyBox);

		skybox.texturedModel.getTexture().bindCubeTexture(2);
		shader.loadRefractionData(refraction.refractiveIndex, refraction.refractiveFactor);
	} else
	{
		shader.loadRefractionData(0.0f, 0.0f);
	}
}

void Survive::ObjectRenderer::addSkybox(entt::entity skybox)
{
	m_SkyBox = skybox;
}

void Survive::ObjectRenderer::renderMaterial(const entt::registry &registry, entt::entity entity,
											 const ObjectShader &shader) const
{
	static glm::vec4 defaultColor{0, 0, 0, 0};

	if (registry.any_of<SpriteComponent>(entity))
	{
		const SpriteComponent &spriteComponent = registry.get<SpriteComponent>(entity);
		shader.loadColor(spriteComponent.color);
	} else
	{
		shader.loadColor(defaultColor);
	}

	if (registry.any_of<MaterialComponent>(entity))
	{
		const MaterialComponent &materialComponent = registry.get<MaterialComponent>(entity);
		shader.loadUseNormalMapping(materialComponent.useNormalMapping);

		materialComponent.normalMap.bindTexture(4);
	} else
	{
		m_DefaultTexture.bindTexture(4);
		shader.loadUseNormalMapping(false);
	}
}

bool Survive::ObjectRenderer::getTransparencyProperty(const entt::registry &registry, entt::entity object)
{
	if (registry.any_of<MaterialComponent>(object))
	{
		const MaterialComponent &rigidBody = registry.get<MaterialComponent>(object);
		return rigidBody.isTransparent;
	}

	return false;
}
