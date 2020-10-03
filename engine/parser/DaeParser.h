//
// Created by david on 09. 06. 2020..
//

#ifndef SURVIVE_DAEPARSER_H
#define SURVIVE_DAEPARSER_H

#include <glm/glm.hpp>
#include <vector>

#include "../renderer/Loader.h"
#include "../animations/joints/Joint.h"

struct VertexData
{
    int size{};
    std::string indicesLine;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textures;
    std::vector<glm::ivec3> jointIds;
    std::vector<glm::vec3> jointWeights;
};

struct AnimationData
{
    std::vector<float> timestamps;
    std::string jointName;
    std::vector<glm::mat4> transforms;
};

struct JointData
{
    Joint rootJoint;
    int numberOfJoints{};
};

class DaeParser
{
private:
    VertexData m_VertexData;
    JointData m_JointData;

    void loadControllers(std::ifstream &reader, std::vector<std::string> &jointNames);

    void loadGeometry(std::ifstream &reader);

    Joint loadVisualScene(std::ifstream &reader, const std::vector<std::string> &jointNames);

    void loadAnimation(std::ifstream &reader);

    void parsePointsLine(std::string &line, std::vector<glm::vec3> &vertices);

    void parseTexturesLine(std::string &line, std::vector<glm::vec2> &textures);

    Model parseIndices(Loader &loader);

    std::vector<std::string> getData(std::string &line);

    void processJointsData(std::vector<float> &resultWeights, std::vector<unsigned> &resultIds, unsigned index);

    glm::mat4 getJointTransform(std::string &line);

    Joint getJoint(std::ifstream &reader, std::string &line, const std::vector<std::string> &jointNames);

    AnimationData getAnimationData(std::ifstream &reader);

    std::vector<glm::mat4> getTransforms(std::string &line);

public:
    Model loadDae(const char *daeFile, Loader &loader);
};


#endif //SURVIVE_DAEPARSER_H
