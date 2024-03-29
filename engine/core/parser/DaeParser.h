//
// Created by david on 09. 06. 2020..
//

#ifndef SURVIVE_DAEPARSER_H
#define SURVIVE_DAEPARSER_H

#include <glm/glm.hpp>
#include <vector>
#include <glm/ext/matrix_transform.hpp>

#include "Loader.h"
#include "Joint.h"
#include "KeyFrame.h"
#include "Animation.h"

namespace Survive
{
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
		size_t numberOfJoints{};
	};

	class DaeParser
	{
	private:
		const glm::mat4 correction = glm::rotate(glm::mat4{1.0f}, glm::radians(-90.0f), glm::vec3{1, 0, 0});

		VertexData m_VertexData;
		JointData m_JointData;
		std::vector<KeyFrame> m_KeyFrames;

		float m_LengthInSeconds;

	public:
		Model loadDae(const std::string &daeFile, Loader &loader);

		[[nodiscard]] Animation getAnimation() const;

		[[nodiscard]] std::pair<Joint, int> getJointData() const;

	private:
		void loadControllers(std::ifstream &reader, std::vector<std::string> &jointNames);

		void loadGeometry(std::ifstream &reader);

		Joint loadVisualScene(std::ifstream &reader, const std::vector<std::string> &jointNames);

		static std::vector<AnimationData> loadAnimation(std::ifstream &reader);

		static void parsePointsLine(std::string &line, std::vector<glm::vec3> &vertices);

		static void parseTexturesLine(std::string &line, std::vector<glm::vec2> &textures);

		Model parseIndices(Loader &loader);

		static std::vector<std::string> getData(std::string &line);

		void processJointsData(std::vector<float> &resultWeights, std::vector<int> &resultIds, unsigned index);

		static glm::mat4 getJointTransform(std::string &line);

		static Joint getJoint(std::ifstream &reader, std::string &line, const std::vector<std::string> &jointNames);

		static AnimationData getAnimationData(std::ifstream &reader);

		static std::vector<glm::mat4> getTransforms(std::string &line);

		std::vector<KeyFrame>
		getKeyFrames(const std::vector<AnimationData> &animationData, const std::string &rootJoint);

		void normalizeWeights();

		std::vector<glm::vec3> applyCorrectionToVertices(const std::vector<glm::vec3> &vertices);
	};
}

#endif //SURVIVE_DAEPARSER_H
