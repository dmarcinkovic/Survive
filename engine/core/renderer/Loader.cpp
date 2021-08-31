//
// Created by david on 24. 03. 2020..
//

#include <iostream>
#include <execution>

#include "Log.h"
#include "Loader.h"
#include "stb_image.h"

std::vector<GLuint> Survive::Loader::m_Textures;

Survive::Model
Survive::Loader::loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices, GLint size)
{
	GLuint vao = createVao();

	createIndexBuffer(indices);
	storeDataInAttributeList(0, vertices, size);

	unbindVao();

	return {vao, static_cast<GLsizei>(indices.size())};
}

Survive::Loader::~Loader()
{
	glDeleteVertexArrays(static_cast<GLsizei>(m_Vaos.size()), m_Vaos.data());
	glDeleteBuffers(static_cast<GLsizei>(m_Vbos.size()), m_Vbos.data());
	glDeleteTextures(1, m_Textures.data());
}

void Survive::Loader::storeDataInAttributeList(GLuint attributeNumber, const std::vector<float> &vertices,
											   GLint size)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(attributeNumber);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	auto bufferSize = static_cast<GLsizeiptr>(vertices.size() * sizeof(float));
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, nullptr);
	m_Vbos.emplace_back(vbo);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
Survive::Loader::storeDataInAttributeList(GLuint attributeNumber, const std::vector<int> &data, GLint size)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(attributeNumber);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	auto dataSize = static_cast<GLsizeiptr>(sizeof(int) * data.size());
	glBufferData(GL_ARRAY_BUFFER, dataSize, data.data(), GL_STATIC_DRAW);
	glVertexAttribIPointer(attributeNumber, size, GL_INT, 0, nullptr);
	m_Vbos.emplace_back(vbo);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Survive::Loader::createIndexBuffer(const std::vector<unsigned> &indices)
{
	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	auto size = static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);

	m_Vbos.emplace_back(indexBuffer);
}

GLuint Survive::Loader::createVao()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	m_Vaos.emplace_back(vao);

	return vao;
}

void Survive::Loader::unbindVao()
{
	glBindVertexArray(0);
}

Survive::Model Survive::Loader::loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices,
										  const std::vector<float> &textureCoordinates, GLint size)
{
	GLuint vao = createVao();

	createIndexBuffer(indices);
	storeDataInAttributeList(0, vertices, size);
	storeDataInAttributeList(1, textureCoordinates, 2);
	unbindVao();

	return {vao, static_cast<GLsizei>(indices.size())};
}

Survive::Model Survive::Loader::loadToVao(const std::vector<float> &vertices,
										  const std::vector<float> &textureCoordinates,
										  const std::vector<float> &normals)
{
	GLuint vao = createVao();

	storeDataInAttributeList(0, vertices, 3);
	storeDataInAttributeList(1, textureCoordinates, 2);
	storeDataInAttributeList(2, normals, 3);
	unbindVao();

	return {vao, static_cast<GLsizei>(vertices.size()) / 3};
}

Survive::Model
Survive::Loader::loadToVao(const std::vector<float> &vertices, const std::vector<float> &textureCoordinates,
						   const std::vector<float> &normals, const std::vector<unsigned int> &indices)
{
	GLuint vao = createVao();

	createIndexBuffer(indices);
	storeDataInAttributeList(0, vertices, 3);
	storeDataInAttributeList(1, textureCoordinates, 2);
	storeDataInAttributeList(2, normals, 3);
	unbindVao();

	return {vao, static_cast<GLsizei>(indices.size())};
}

Survive::Model Survive::Loader::loadToVao(const std::vector<float> &vertices, const std::vector<float> &textures,
										  const std::vector<float> &normals, const std::vector<float> &jointWeights,
										  const std::vector<int> &jointIds)
{
	GLuint vao = createVao();

	storeDataInAttributeList(0, vertices, 3);
	storeDataInAttributeList(1, textures, 2);
	storeDataInAttributeList(2, normals, 3);
	storeDataInAttributeList(3, jointWeights, 3);
	storeDataInAttributeList(4, jointIds, 3);

	return {vao, static_cast<GLsizei>(vertices.size()) / 3};
}

void
Survive::Loader::updateFloatData(const std::vector<float> &vertices, const std::vector<float> &textures, GLuint vaoId)
{
	glBindVertexArray(vaoId);

	storeDataInAttributeList(0, vertices, 2);
	storeDataInAttributeList(1, textures, 2);

	unbindVao();
}

Survive::Model Survive::Loader::loadToVao(const std::vector<float> &vertices,
										  const std::vector<float> &textureCoordinates, GLsizei size)
{
	GLuint vao = createVao();

	storeDataInAttributeList(0, vertices, size);
	storeDataInAttributeList(1, textureCoordinates, 2);
	unbindVao();

	return {vao, static_cast<GLsizei>(vertices.size()) / size};
}

Survive::Model Survive::Loader::loadToVao(const std::vector<float> &vertices, GLsizei size)
{
	GLuint vao = createVao();

	storeDataInAttributeList(0, vertices, size);
	unbindVao();

	return {vao, static_cast<GLsizei>(vertices.size()) / size};
}

void Survive::Loader::addMipMap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4);
}

Survive::Texture Survive::Loader::loadTexture(const char *texture) noexcept
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	bool loaded = loadImage(texture);
	if (!loaded)
	{
		textureId = 0;
	}

	addMipMap();

	glBindTexture(GL_TEXTURE_2D, 0);

	m_Textures.emplace_back(textureId);
	return Texture(textureId);
}

bool Survive::Loader::loadImage(const char *texture) noexcept
{
	stbi_set_flip_vertically_on_load(1);

	int width, height, BPP;
	unsigned char *image = stbi_load(texture, &width, &height, &BPP, 4);

	if (!image)
	{
		std::string message = "Error while loading " + std::string(texture);
		Log::logWindow(LogType::ERROR, message);
		std::cout << message << '\n';

		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);

	return true;
}

std::unordered_map<const char *, Survive::Texture>
Survive::Loader::loadTextures(const std::vector<const char *> &textures)
{
	stbi_set_flip_vertically_on_load(1);

	auto images = loadImages(textures);

	std::unordered_map<const char *, Texture> result;
	for (auto const&[filename, imageData]: images)
	{
		GLuint textureId = loadTexture(imageData);

		result[filename] = Texture(textureId);
	}

	return result;
}

std::vector<Survive::Texture> Survive::Loader::loadAllTextures(const std::vector<const char *> &textures)
{
	stbi_set_flip_vertically_on_load(1);

	auto images = loadImages(textures);
	std::vector<Texture> result;

	for (auto const &filename: textures)
	{
		auto const &imageData = images[filename];

		result.emplace_back(loadTexture(imageData));
	}

	return result;
}

GLuint Survive::Loader::loadTexture(const std::tuple<std::uint8_t *, int, int> &imageData)
{
	std::uint8_t *image = std::get<0>(imageData);
	int width = std::get<1>(imageData);
	int height = std::get<2>(imageData);

	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);

	glBindTexture(GL_TEXTURE_2D, 0);
	m_Textures.emplace_back(textureId);

	return textureId;
}

std::unordered_map<const char *, std::tuple<std::uint8_t *, int, int>>
Survive::Loader::loadImages(const std::vector<const char *> &textures)
{
	std::unordered_map<const char *, std::tuple<std::uint8_t *, int, int>> images;

	std::for_each(std::execution::par, textures.begin(), textures.end(), [&](const char *filename) {
		int width, height, BPP;
		std::uint8_t *image = stbi_load(filename, &width, &height, &BPP, 4);

		images[filename] = std::make_tuple(image, width, height);
	});

	return images;
}

Survive::Model Survive::Loader::renderQuad()
{
	static const std::vector<float> vertices{-1, -1, 1, -1, 1, 1, -1, 1};
	static const std::vector<unsigned> indices{0, 1, 3, 3, 1, 2};

	return Model(loadToVao(vertices, indices, 2));
}

Survive::Model Survive::Loader::renderQuadStrip()
{
	static const std::vector<float> vertices{-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f};

	return loadToVao(vertices, 2);
}

Survive::Model Survive::Loader::renderCube()
{
	static const std::vector<float> vertices{-1, 1, -1, -1, -1, -1, 1, -1, -1, 1, 1, -1,
											 -1, -1, 1, -1, 1, 1, 1, -1, 1, 1, 1, 1};

	static const std::vector<unsigned> indices{0, 1, 2, 2, 3, 0, 4, 1, 0, 0, 5, 4, 2, 6, 7, 7, 3, 2,
											   4, 5, 7, 7, 6, 4, 0, 3, 7, 7, 5, 0, 1, 4, 2, 2, 4, 6};

	return Model(loadToVao(vertices, indices, 3));
}

Survive::Texture Survive::Loader::loadCubeMap(const std::vector<const char *> &faces) noexcept
{
	GLuint cubeMap;
	glGenTextures(1, &cubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	loadToCubeMap(faces);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	m_Textures.emplace_back(cubeMap);

	return Texture(cubeMap);
}

Survive::Texture Survive::Loader::loadCubeMap(const std::vector<std::string> &faces)
{
	std::vector<const char *> newFaces(faces.size());
	for (int i = 0; i < faces.size(); ++i)
	{
		newFaces[i] = faces[i].c_str();
	}

	return loadCubeMap(newFaces);
}

void Survive::Loader::loadToCubeMap(const std::vector<const char *> &faces) noexcept
{
	stbi_set_flip_vertically_on_load(0);

	auto images = loadImages(faces);

	for (int i = 0; i < faces.size(); ++i)
	{
		auto const &imageData = images[faces[i]];

		std::uint8_t *image = std::get<0>(imageData);
		int width = std::get<1>(imageData);
		int height = std::get<2>(imageData);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
					 image);
		stbi_image_free(image);
	}
}

GLuint Survive::Loader::createEmptyVBO(GLsizeiptr vertexCount)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);

	m_Vbos.emplace_back(vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * static_cast<GLsizeiptr >(sizeof(float)), nullptr, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}

void Survive::Loader::updateVBO(GLuint vbo, const std::vector<float> &data, GLsizeiptr sizeOfData)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLsizeiptr dataSize = sizeOfData * static_cast<GLsizeiptr>(sizeof(float));
	glBufferData(GL_ARRAY_BUFFER, dataSize, data.data(), GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, data.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Survive::Loader::addInstancedAttribute(GLuint vao, GLuint vbo, GLuint attribute, int vertexCount,
											GLsizei instancedDataLength,
											int offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);

	const void *pointer = reinterpret_cast<void *>(offset * sizeof(float));
	glVertexAttribPointer(attribute, vertexCount, GL_FLOAT, GL_FALSE,
						  instancedDataLength * static_cast<GLsizei>(sizeof(float)), pointer);

	glVertexAttribDivisor(attribute, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Survive::Model::Model(GLuint vao, GLsizei vertexCount)
		: m_Vao(vao), m_VertexCount(vertexCount)
{

}

bool Survive::Model::isValidModel() const
{
	return m_Vao != 0 && m_VertexCount != 0;
}
