//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_LOADER_H
#define SURVIVE_LOADER_H

#include <vector>
#include <GL/glew.h>

struct Model
{
    GLuint m_Vao{};
    size_t m_VertexCount{};

    Model(GLuint vao, size_t vertexCount);

    Model() = default;
};

class Loader
{
private:
    std::vector<GLuint> m_Vaos;
    std::vector<GLuint> m_Vbos;

    static std::vector<GLuint> m_Textures;

public:
    Model loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices, size_t size);

    ~Loader();

    static void unbindVao();

    Model loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices,
                    const std::vector<float> &textureCoordinates, size_t size);

    Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textureCoordinates,
                    const std::vector<float> &normals);

    Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textures,
                    const std::vector<float> &normals, const std::vector<float> &jointWeights,
                    const std::vector<unsigned> &jointIds);

    Model loadToVao(const std::vector<float> &vertices, const std::vector<float> &textureCoordinates, size_t size);

    static GLuint loadTexture(const char *texture) noexcept;

    static GLuint loadCubeMap(const std::vector<std::string> &faces) noexcept;

    Model renderQuad();

    Model renderCube();

    void updateFloatData(const std::vector<float> &vertices, const std::vector<float> &textures, GLuint vaoId);

private:
    void storeDataInAttributeList(GLuint attributeNumber, const std::vector<float> &vertices, size_t size,
                                  GLenum usage = GL_STATIC_DRAW);

    void storeDataInAttributeList(GLuint attributeNumber, const std::vector<unsigned> &data, size_t size);

    void createIndexBuffer(const std::vector<unsigned> &indices);

    GLuint createVao();

    static void loadImage(const char *texture) noexcept;

    static void addMipMap();

    static void loadToCubeMap(const std::vector<std::string> &faces) noexcept;
};


#endif //SURVIVE_LOADER_H
