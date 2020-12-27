//
// Created by david on 17. 05. 2020..
//
#include "ObjectRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"

ObjectRenderer::ObjectRenderer(const Light &light)
		: m_Light(light)
{
}

void ObjectRenderer::render(const Camera &camera, GLuint shadowMap) const
{
	Renderer3DUtil::prepareRendering(m_Shader);

	loadUniforms(camera, shadowMap);

	for (auto const&[texturedModel, objects] : m_Objects)
	{
		Renderer3DUtil::prepareEntity(texturedModel);
		renderScene(objects, camera);

		Renderer3DUtil::finishRenderingEntity();
	}

	Renderer3DUtil::finishRendering();
}

void ObjectRenderer::add3DObject(Object3D &entity)
{
	auto &batch = m_Objects[entity.m_Texture];
	batch.emplace_back(entity);
}

void
ObjectRenderer::renderScene(const std::vector<std::reference_wrapper<Object3D>> &objects, const Camera &camera) const
{
	for (auto const &object : objects)
	{
		auto const &o = object.get();
		loadObjectUniforms(o, camera);

		if (o.m_DrawOutline)
		{
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
		}

		Renderer3DUtil::addTransparency(!o.m_IsTransparent, !o.m_IsTransparent);

		glDrawArrays(GL_TRIANGLES, 0, o.m_Texture.vertexCount());

		Renderer3DUtil::addTransparency(o.m_IsTransparent, o.m_IsTransparent);
		Texture::unbindCubeTexture();
	}
}

void ObjectRenderer::loadUniforms(const Camera &camera, GLuint shadowMap) const
{
	const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	const glm::mat4 lightViewMatrix = Maths::createLightViewMatrix(m_Light);
	m_Shader.loadLight(m_Light.position(), m_Light.color(), 0.7, 3);

	m_Shader.loadViewMatrix(viewMatrix);
	m_Shader.loadLightViewMatrix(lightViewMatrix);
	m_Shader.loadTextures();
	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadLightProjection(Maths::lightProjectionMatrix);

	Texture texture(shadowMap);
	texture.bindTexture(1);
	m_Shader.loadCameraPosition(camera.m_Position);
}

void ObjectRenderer::loadObjectUniforms(const Object3D &object, const Camera &camera) const
{
	auto rotation = camera.m_Rotation + object.m_Rotation;

	object.m_Skybox.bindCubeTexture(2);
	m_Shader.loadReflectiveFactor(object.m_ReflectiveFactor);
	m_Shader.loadRefractionData(object.m_RefractiveIndex, object.m_RefractionFactor);

	glm::mat4 modelMatrix = Maths::createTransformationMatrix(object.m_Position, object.m_ScaleX, object.m_ScaleY,
															  object.m_ScaleZ, rotation.x, rotation.y, rotation.z);
	m_Shader.loadTransformationMatrix(modelMatrix);
}

