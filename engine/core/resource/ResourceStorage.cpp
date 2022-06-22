//
// Created by david on 13.06.22..
//

#include "ResourceStorage.h"

Survive::ResourceStorage &Survive::ResourceStorage::get()
{
	static ResourceStorage storage;
	return storage;
}

void Survive::ResourceStorage::setTexture(const std::string &texturePath, const Texture &texture)
{
	m_Textures[texturePath] = texture;
}

void Survive::ResourceStorage::setModel(const std::string &modelPath, const Model &model)
{
	m_Models[modelPath] = model;
}

bool Survive::ResourceStorage::isTextureAlreadyLoaded(const std::string &texturePath) const
{
	return m_Textures.contains(texturePath);
}

const Survive::Texture &Survive::ResourceStorage::getTexture(const std::string &texturePath) const
{
	return m_Textures.at(texturePath);
}

bool Survive::ResourceStorage::isModelAlreadyLoaded(const std::string &modelPath) const
{
	return m_Models.contains(modelPath);
}

const Survive::Model &Survive::ResourceStorage::getModel(const std::string &modelPath) const
{
	return m_Models.at(modelPath);
}

void Survive::ResourceStorage::setAnimation(const std::string &modelPath, float lengthInSeconds,
											const std::vector<KeyFrame> &keyFrames)
{
	m_Animations[modelPath] = std::make_pair(lengthInSeconds, keyFrames);
}

const Survive::ResourceStorage::AnimationData &
Survive::ResourceStorage::getAnimation(const std::string &modelPath) const
{
	return m_Animations.at(modelPath);
}

bool Survive::ResourceStorage::isAnimationAlreadyLoaded(const std::string &modelPath) const
{
	return m_Animations.contains(modelPath);
}

bool Survive::ResourceStorage::isJointDataAlreadyLoaded(const std::string &modelPath) const
{
	return m_JointsData.contains(modelPath);
}

const Survive::ResourceStorage::JointData &Survive::ResourceStorage::getJointData(const std::string &modelPath) const
{
	return m_JointsData.at(modelPath);
}

void Survive::ResourceStorage::setJointData(const std::string &modelPath, const Survive::Joint &rootJoint,
											int numberOfJoints)
{
	m_JointsData[modelPath] = std::make_pair(rootJoint, numberOfJoints);
}
