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

		static std::vector<GLuint> m_Textures;

	public:
		Model loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices, GLint size);

		~Loader();

		static void unbindVao();

		Model loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices,
						const std::vector<float> &textureCoordinates, GLint size);

		Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textureCoordinates,
						const std::vector<float> &normals);

		Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textureCoordinates,
						const std::vector<float> &normals, const std::vector<unsigned> &indices);

		Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textures,
						const std::vector<float> &normals, const std::vector<float> &jointWeights,
						const std::vector<int> &jointIds);

		Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textureCoordinates, GLsizei size);

		Model loadToVao(const std::vector<float> &vertices, GLsizei size);

		static Texture loadTexture(const char *texture) noexcept;

		static std::unordered_map<const char *, Texture> loadTextures(const std::vector<const char *> &textures);

		static std::vector<Texture> loadAllTextures(const std::vector<const char *> &textures);

		static Texture loadCubeMap(const std::vector<const char *> &faces) noexcept;

		static Texture loadCubeMap(const std::vector<std::string> &faces);

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

		void storeDataInAttributeList(GLuint attributeNumber, const std::vector<int> &data, GLint size);

		void createIndexBuffer(const std::vector<unsigned> &indices);

		GLuint createVao();

		static bool loadImage(const char *texture) noexcept;

		static void addMipMap();

		static void loadToCubeMap(const std::vector<const char *> &faces) noexcept;

		static std::unordered_map<const char *, std::tuple<std::uint8_t *, int, int>>
		loadImages(const std::vector<const char *> &textures);

		static GLuint loadTexture(const std::tuple<std::uint8_t *, int, int> &imageData);
	};
}

#endif //SURVIVE_LOADER_H
