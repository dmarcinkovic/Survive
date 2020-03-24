//
// Created by david on 24. 03. 2020..
//

#include "Loader.h"

Model Loader::loadToVao(const std::vector<float> &vertices, const std::vector<unsigned> &indices, size_t size)
{
    GLuint vao = createVao();

    createIndexBuffer(indices);
    storeDataInAttributeList(0, vertices, size);

    return Model(vao, indices.size());
}

Loader::~Loader()
{
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
}

void Loader::storeDataInAttributeList(GLuint attributeNumber, const std::vector<float> &vertices, size_t size)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, nullptr);
    vbos.emplace_back(vbo);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::createIndexBuffer(const std::vector<unsigned> &indices)
{
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);

    vbos.emplace_back(indexBuffer);
}

GLuint Loader::createVao()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    vaos.emplace_back(vao);

    return vao;
}

void Loader::unbindVao()
{
    glBindVertexArray(0);
}

Model::Model(GLuint vao, size_t vertexCount)
        : vao(vao), vertexCount(vertexCount)
{

}
