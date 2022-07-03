//
// Created by david on 13.06.22..
//

#ifndef SURVIVE_RESOURCESTORAGE_H
#define SURVIVE_RESOURCESTORAGE_H

#include <unordered_map>
#include <string>

#include "TexturedModel.h"
#include "KeyFrame.h"
#include "Joint.h"

namespace Survive
{
	class ResourceStorage
	{
	private:
		using JointData = std::pair<Joint, int>;
		using AnimationData = std::pair<float, std::vector<KeyFrame>>;

		std::unordered_map<std::string, Texture> m_Textures;
		std::unordered_map<std::string, Model> m_Models;
		std::unordered_map<std::string, AnimationData> m_Animations;
		std::unordered_map<std::string, JointData> m_JointsData;

	public:
		static ResourceStorage &get();

		ResourceStorage(const ResourceStorage &) = delete;

		bool isTextureAlreadyLoaded(const std::string &texturePath) const;

		const Texture &getTexture(const std::string &texturePath) const;

		void setTexture(const std::string &texturePath, const Texture &texture);

		bool isModelAlreadyLoaded(const std::string &modelPath) const;

		const Model &getModel(const std::string &modelPath) const;

		void setModel(const std::string &modelPath, const Model &model);

		void setAnimation(const std::string &modelPath, float lengthInSeconds, const std::vector<KeyFrame> &keyFrames);

		const AnimationData &getAnimation(const std::string &modelPath) const;

		bool isAnimationAlreadyLoaded(const std::string &modelPath) const;

		bool isJointDataAlreadyLoaded(const std::string &modelPath) const;

		const JointData &getJointData(const std::string &modelPath) const;

		void setJointData(const std::string &modelPath, const Joint &rootJoint, int numberOfJoints);

	private:
		ResourceStorage() = default;
	};
}

#endif //SURVIVE_RESOURCESTORAGE_H
