//
// Created by david on 09. 06. 2020..
//

#include <fstream>
#include <iostream>
#include <glm/ext/matrix_transform.hpp>

#include "DaeParser.h"
#include "../util/Util.h"

Model DaeParser::loadDae(const char *daeFile, Loader &loader)
{
	std::ifstream reader(daeFile);
	std::vector<std::string> jointNames;
	std::vector<AnimationData> animationData;

	if (!reader)
	{
		std::cout << "Could not open: " << daeFile << '\n';
	}

	std::string line;
	while (std::getline(reader, line))
	{
		if (line.find("<library_geometries>") != -1)
		{
			loadGeometry(reader);
		} else if (line.find("<library_controllers>") != -1)
		{
			loadControllers(reader, jointNames);
			m_JointData.numberOfJoints = jointNames.size();
		} else if (line.find("<library_visual_scenes>") != -1)
		{
			m_JointData.rootJoint = loadVisualScene(reader, jointNames);
			m_KeyFrames = getKeyFrames(animationData, m_JointData.rootJoint.name());
		} else if (line.find("<library_animations>") != -1)
		{
			animationData = loadAnimation(reader);
		}
	}

	reader.close();
	return parseIndices(loader);
}

Animation DaeParser::getAnimation() const
{
	return Animation(m_LengthInSeconds, m_KeyFrames);
}

std::pair<Joint, int> DaeParser::getJointData() const
{
	return {m_JointData.rootJoint, m_JointData.numberOfJoints};
}

void DaeParser::loadGeometry(std::ifstream &reader)
{
	static const glm::mat4 correction = glm::rotate(glm::mat4{1.0f}, glm::radians(-90.0f), glm::vec3{1, 0, 0});

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textures;

	int coordinatesSize = 0;

	std::string line;
	while (std::getline(reader, line))
	{
		if (vertices.empty() && line.find("positions-array") != -1)
		{
			parsePointsLine(line, vertices);
		} else if (normals.empty() && line.find("normals-array") != -1)
		{
			parsePointsLine(line, normals);
		} else if (textures.empty() && line.find("map-0-array") != -1)
		{
			parseTexturesLine(line, textures);
		} else if (line.find("<p>") != -1)
		{
			m_VertexData.indicesLine = line;
			m_VertexData.size = coordinatesSize + 1;
			m_VertexData.vertices = applyCorrectionToVertices(vertices, correction);
			m_VertexData.textures = textures;
			m_VertexData.normals = applyCorrectionToVertices(normals, correction);
			break;
		} else if (line.find("input semantic") != -1)
		{
			int index = line.find("offset");
			if (index != -1)
			{
				char c = line[index + 8];
				coordinatesSize = c - '0';
			}
		}
	}
}

void DaeParser::parsePointsLine(std::string &line, std::vector<glm::vec3> &vertices)
{
	int index = line.find('>');
	auto numbers = Util::split(line.substr(index + 1), ' ');

	for (int i = 0; i < numbers.size(); i += 3)
	{
		float x = std::stof(numbers[i]);
		float y = std::stof(numbers[i + 1]);
		float z = std::stof(numbers[i + 2]);
		vertices.emplace_back(x, y, z);
	}
}

void DaeParser::parseTexturesLine(std::string &line, std::vector<glm::vec2> &textures)
{
	int index = line.find('>');
	auto numbers = Util::split(line.substr(index + 1), ' ');

	for (int i = 0; i < numbers.size(); i += 2)
	{
		float x = std::stof(numbers[i]);
		float y = std::stof(numbers[i + 1]);
		textures.emplace_back(x, y);
	}
}

Model DaeParser::parseIndices(Loader &loader)
{
	int index = m_VertexData.indicesLine.find('>');
	auto numbers = Util::split(m_VertexData.indicesLine.substr(index + 1), ' ');

	std::vector<float> resultPoints;
	std::vector<float> resultNormals;
	std::vector<float> resultTextures;
	std::vector<float> resultWeights;
	std::vector<int> resultIds;

	for (int i = 0; i < numbers.size(); i += m_VertexData.size)
	{
		unsigned vertexIndex = std::stoi(numbers[i]);
		unsigned normalIndex = std::stoi(numbers[i + 1]);
		unsigned textureIndex = std::stoi(numbers[i + 2]);

		Util::processVertex(m_VertexData.vertices, m_VertexData.normals, m_VertexData.textures,
							resultPoints, resultNormals, resultTextures,
							vertexIndex, textureIndex, normalIndex);

		processJointsData(resultWeights, resultIds, vertexIndex);
	}

	return loader.loadToVao(resultPoints, resultTextures, resultNormals, resultWeights, resultIds);
}

void DaeParser::loadControllers(std::ifstream &reader, std::vector<std::string> &jointNames)
{
	std::vector<float> weights;
	std::vector<int> count;
	std::vector<glm::ivec3> jointIds;
	std::vector<glm::vec3> jointWeights;

	std::string line;
	while (std::getline(reader, line))
	{
		if (jointNames.empty() && line.find("skin-joints-array") != -1)
		{
			jointNames = getData(line);
		} else if (weights.empty() && line.find("skin-weights-array") != -1)
		{
			auto numbers = getData(line);
			weights.reserve(numbers.size());

			for (auto const &weight : numbers)
			{
				weights.emplace_back(std::stof(weight));
			}
		} else if (count.empty() && line.find("<vcount>") != -1)
		{
			auto numbers = getData(line);
			count.reserve(numbers.size());

			for (auto const &c : numbers)
			{
				count.emplace_back(std::stoi(c));
			}
		} else if (line.find("<v>") != -1)
		{
			auto numbers = getData(line);

			int index = 0;
			for (int n : count)
			{
				int numberOfJoints = std::min(n, 3);

				glm::vec3 jointWeight{0, 0, 0};
				glm::ivec3 jointId{-1, -1, -1};
				for (int i = 0; i < 2 * numberOfJoints; i += 2)
				{
					int j = i / 2;
					jointId[j] = std::stoi(numbers[index++]);
					jointWeight[j] = weights[std::stof(numbers[index++])];
				}

				jointIds.emplace_back(jointId);
				jointWeights.emplace_back(jointWeight);

				if (n > numberOfJoints)
				{
					index += 2 * (n - numberOfJoints);
				}
			}

			m_VertexData.jointWeights = jointWeights;
			m_VertexData.jointIds = jointIds;
			break;
		}
	}

	normalizeWeights();
}

void DaeParser::normalizeWeights()
{
	for (glm::vec3 &vec : m_VertexData.jointWeights)
	{
		float sum = vec.x + vec.y + vec.z;

		if (sum < 1.0f)
		{
			vec.x /= sum;
			vec.y /= sum;
			vec.z /= sum;
		}
	}
}

std::vector<std::string> DaeParser::getData(std::string &line)
{
	int start = line.find('>');
	int end = line.find_last_of('<');

	if (end == -1)
	{
		end = line.length();
	}

	return Util::split(line.substr(start + 1, end - start - 1), ' ');
}

void DaeParser::processJointsData(std::vector<float> &resultWeights, std::vector<int> &resultIds,
								  unsigned int index)
{
	const auto &weight = m_VertexData.jointWeights[index];
	resultWeights.emplace_back(weight.x);
	resultWeights.emplace_back(weight.y);
	resultWeights.emplace_back(weight.z);

	const auto &id = m_VertexData.jointIds[index];
	resultIds.emplace_back(id.x);
	resultIds.emplace_back(id.y);
	resultIds.emplace_back(id.z);
}

Joint DaeParser::loadVisualScene(std::ifstream &reader, const std::vector<std::string> &jointNames)
{
	static const glm::mat4 correction = glm::rotate(glm::mat4{1.0f}, glm::radians(-90.0f), glm::vec3{1, 0, 0});

	std::string line;
	bool initialized = false;
	Joint root;

	std::stack<Joint> stack;

	while (std::getline(reader, line))
	{
		if (line.find("type=\"JOINT\"") != -1)
		{
			Joint rootJoint = getJoint(reader, line, jointNames);
			stack.push(rootJoint);
			initialized = true;
		} else if (line.find("</node>") != -1 && initialized)
		{
			Joint joint = stack.top();
			stack.pop();

			if (!stack.empty())
			{
				stack.top().addChild(joint);
			} else
			{
				root = joint;
				break;
			}
		}
	}

	root.applyCorrection(correction);
	return root;
}

Joint DaeParser::getJoint(std::ifstream &reader, std::string &line, const std::vector<std::string> &jointNames)
{
	static const int OFFSET = 4;

	const int startIndex = line.find("id=");
	std::string restOfLine = line.substr(startIndex + OFFSET);
	const int length = restOfLine.find('\"');

	std::string name = restOfLine.substr(0, length);
	int index = std::find(jointNames.begin(), jointNames.end(), name) - jointNames.begin();

	std::getline(reader, line);

	return Joint(name, index, getJointTransform(line));
}

glm::mat4 DaeParser::getJointTransform(std::string &line)
{
	auto data = getData(line);
	glm::mat4 transform{};

	static const int SIZE = 4;

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			int index = i * SIZE + j;
			transform[i][j] = std::stof(data[index]);
		}
	}

	return transform;
}

std::vector<AnimationData> DaeParser::loadAnimation(std::ifstream &reader)
{
	std::string line;
	std::vector<AnimationData> animationData;

	while (std::getline(reader, line))
	{
		if (line.find("</library_animations>") != -1)
		{
			break;
		} else if (line.find("animation id") != -1)
		{
			animationData.emplace_back(getAnimationData(reader));
		}
	}

	return animationData;
}

AnimationData DaeParser::getAnimationData(std::ifstream &reader)
{
	AnimationData animationData;
	std::string line;
	while (std::getline(reader, line))
	{
		if (line.find("</animation>") != -1)
		{
			break;
		} else if (line.find("target") != -1)
		{
			auto start = line.find_last_of('=') + 1;
			auto end = line.find('/') - 1;

			animationData.jointName = line.substr(start + 1, end - start);
		} else if (line.find("input-array") != -1 && line.find("float_array") != -1)
		{
			auto timestamps = getData(line);

			for (auto const &timestamp : timestamps)
			{
				animationData.timestamps.emplace_back(std::stof(timestamp));
			}
		} else if (line.find("output-array") != -1 && line.find("float_array") != -1)
		{
			animationData.transforms = getTransforms(line);
		}
	}

	return animationData;
}

std::vector<glm::mat4> DaeParser::getTransforms(std::string &line)
{
	auto data = getData(line);
	std::vector<glm::mat4> transforms;

	static const int SIZE = 4;

	int n = static_cast<int>(data.size()) / (SIZE * SIZE);
	int index = 0;

	for (int i = 0; i < n; ++i)
	{
		glm::mat4 transform{};
		for (int row = 0; row < SIZE; ++row)
		{
			for (int col = 0; col < SIZE; ++col)
			{
				transform[row][col] = std::stof(data[index++]);
			}
		}
		transforms.emplace_back(transform);
	}

	return transforms;
}

std::vector<KeyFrame>
DaeParser::getKeyFrames(const std::vector<AnimationData> &animationData, const std::string &rootJoint)
{
	static const glm::mat4 correction = glm::rotate(glm::mat4{1.0f}, glm::radians(-90.0f), glm::vec3{1, 0, 0});

	std::vector<KeyFrame> keyFrames;
	std::vector<float> timeStamps = animationData.front().timestamps;
	for (int i = 0; i < timeStamps.size(); ++i)
	{
		std::unordered_map<std::string, JointTransform> pose;
		for (auto const &j : animationData)
		{
			const glm::mat4 &mat = j.transforms[i];

			glm::mat4 matrix = j.jointName == rootJoint ? correction * glm::transpose(mat) : glm::transpose(mat);
			glm::vec3 translation{matrix[3][0], matrix[3][1], matrix[3][2]};

			JointTransform jointTransform(translation, Quaternion::fromMatrix(matrix));
			pose.insert({j.jointName, jointTransform});
		}
		keyFrames.emplace_back(timeStamps[i], pose);
	}

	m_LengthInSeconds = timeStamps.back();

	return keyFrames;
}

std::vector<glm::vec3>
DaeParser::applyCorrectionToVertices(const std::vector<glm::vec3> &vertices, const glm::mat4 &correction)
{
	std::vector<glm::vec3> result;
	result.reserve(vertices.size());

	for (auto const& vertex : vertices)
	{
		glm::vec4 point(vertex, 1.0f);
		point = correction * point;

		result.emplace_back(point);
	}

	return result;
}
