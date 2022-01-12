//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_LOADER_H
#define SURVIVE_LOADER_H

#include <vector>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <GL/glew.h>

#include "Texture.h"

namespace Survive
{
	struct Model
	{
		GLuint m_Vao{};
		GLsizei m_VertexCount{};

		Model(GLuint vao, GLsizei vertexCount);

		Model() = default;

		[[nodiscard]] bool isValidModel() const;
	};

	class Loader
	{
	private:
		std::vector<GLuint> m_Vaos;
		std::vector<GLuint> m_Vbos;

		std::vector<GLuint> m_Textures;

	public:
		Model loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices, GLint size);

		~Loader();

		static void unbindVao();

		Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textureCoordinates,
						const std::vector<float> &normals, const std::vector<unsigned> &indices);

		Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textures,
						const std::vector<float> &normals, const std::vector<float> &jointWeights,
						const std::vector<int> &jointIds, const std::vector<unsigned> &indices);

		Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textureCoordinates, GLsizei size);

		Model loadToVao(const std::vector<float> &vertices, GLsizei size);

		Texture loadTexture(const char *texture);

		std::unordered_map<const char *, Texture> loadTextures(const std::vector<const char *> &textures);

		std::vector<Texture> loadAllTextures(const std::vector<const char *> &textures);

		Texture loadCubeMap(const std::vector<const char *> &faces);

		Texture loadCubeMap(const std::vector<std::string> &faces);

		Model renderQuad();

		Model renderQuadStrip();

		Model renderCube();

		GLuint createEmptyVBO(GLsizeiptr vertexCount);

		static void updateVBO(GLuint vbo, const std::vector<float> &data, GLsizeiptr sizeOfData);

		static void
		addInstancedAttribute(GLuint vao, GLuint vbo, GLuint attribute, int vertexCount, int instancedDataLength,
							  int offset);

		void updateFloatData(const std::vector<float> &vertices, const std::vector<float> &textures, GLuint vaoId);

	private:
		void storeDataInAttributeList(GLuint attributeNumber, const std::vector<float> &vertices, GLint size);

		void storeDataInAttributeList(const std::vector<int> &data);

		void createIndexBuffer(const std::vector<unsigned> &indices);

		GLuint createVao();

		static void loadImage(const char *texture);

		static void addMipMap();

		static void loadToCubeMap(const std::vector<const char *> &faces);

		static std::unordered_map<const char *, std::tuple<std::uint8_t *, int, int>>
		loadImages(const std::vector<const char *> &textures);

		GLuint loadTexture(const std::tuple<std::uint8_t *, int, int> &imageData);
	};
}

#endif //SURVIVE_LOADER_H
