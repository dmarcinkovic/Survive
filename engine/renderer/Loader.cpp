//
// Created by david on 24. 03. 2020..
//

#include <iostream>
#include "Loader.h"
#include "../texture/stb_image.h"
#include "../texture/Texture.h"

Model Loader::loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices, size_t size)
{
    GLuint vao = createVao();

    createIndexBuffer(indices);
    storeDataInAttributeList(0, vertices, size);

    unbindVao();

    return Model(vao, indices.size());
}

Loader::~Loader()
{
    glDeleteVertexArrays(m_Vaos.size(), m_Vaos.data());
    glDeleteBuffers(m_Vbos.size(), m_Vbos.data());
    glDeleteTextures(1, m_Textures.data());
}

void
Loader::storeDataInAttributeList(GLuint attributeNumber, const std::vector<float> &vertices, size_t size, GLenum usage)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glEnableVertexAttribArray(attributeNumber);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), usage);

    glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, nullptr);
    m_Vbos.emplace_back(vbo);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::createIndexBuffer(const std::vector<unsigned> &indices)
{
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);

    m_Vbos.emplace_back(indexBuffer);
}

GLuint Loader::createVao()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    m_Vaos.emplace_back(vao);

    return vao;
}

void Loader::unbindVao()
{
    glBindVertexArray(0);
}

Model Loader::loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices,
                        const std::vector<float> &textureCoordinates, size_t size)
{
    GLuint vao = createVao();

    createIndexBuffer(indices);
    storeDataInAttributeList(0, vertices, size);
    storeDataInAttributeList(1, textureCoordinates, 2);
    unbindVao();

    return Model(vao, indices.size());
}

Model Loader::loadToVaoDynamic(const std::vector<float> &vertices, const std::vector<float> &texture, size_t size)
{
    GLuint vao = createVao();

    storeDataInAttributeList(0, vertices, size);
    storeDataInAttributeList(1, texture, 2, GL_DYNAMIC_DRAW);
    unbindVao();

    return Model(vao, vertices.size() / size);
}

Model Loader::loadToVao(const std::vector<float> &vertices, const std::vector<float> &textureCoordinates, size_t size)
{
    GLuint vao = createVao();

    storeDataInAttributeList(0, vertices, size);
    storeDataInAttributeList(1, textureCoordinates, 2);
    unbindVao();

    return Model(vao, vertices.size() / size);
}

GLuint Loader::loadTexture(const char *texture) noexcept
{
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    loadImage(texture);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_Textures.emplace_back(textureId);
    return textureId;
}

void Loader::loadImage(const char *texture) noexcept
{
    stbi_set_flip_vertically_on_load(1);

    int width, height, BPP;
    unsigned char *image = stbi_load(texture, &width, &height, &BPP, 4);

    if (!image)
    {
        std::cout << "Error while loading image\n";
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
}

Model::Model(GLuint vao, size_t vertexCount)
        : m_Vao(vao), m_VertexCount(vertexCount)
{

}
