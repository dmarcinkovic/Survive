//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_LOADER_H
#define SURVIVE_LOADER_H

#include <vector>
#include <GL/glew.h>

struct Model
{
    GLuint vao;
    size_t vertexCount;

    Model(GLuint vao, size_t vertexCount);
};

class Loader
{
private:
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    std::vector<GLuint> textures;

    void storeDataInAttributeList(GLuint attributeNumber, const std::vector<float> &vertices, size_t size);

    void createIndexBuffer(const std::vector<unsigned> &indices);

    GLuint createVao();

public:
    Model loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices, size_t size);

    ~Loader();

    static void unbindVao();

    Model loadTexture(const std::vector<float> &vertices, const std::vector<unsigned> &indices,
                        const std::vector<float> &textureCoordinates, size_t size);

    GLuint loadTexture(const char *texture) noexcept;
};


#endif //SURVIVE_LOADER_H
