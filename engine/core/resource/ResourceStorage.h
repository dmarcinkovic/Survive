//
// Created by david on 13.06.22..
//

#ifndef SURVIVE_RESOURCESTORAGE_H
#define SURVIVE_RESOURCESTORAGE_H

#include <unordered_map>
#include <string>

#include "TexturedModel.h"

namespace Survive
{
	class ResourceStorage
	{
	private:
		std::unordered_map<std::string, Texture> m_Textures;
		std::unordered_map<std::string, Model> m_Models;

	public:
		static ResourceStorage &get();

		ResourceStorage(const ResourceStorage &) = delete;

		bool isTextureAlreadyLoaded(const std::string &texturePath) const;

		const Texture &getTexture(const std::string &texturePath) const;

		void setTexture(const std::string &texturePath, const Texture &texture);

		bool isModelAlreadyLoaded(const std::string &modelPath) const;

		const Model &getModel(const std::string &modelPath) const;

		void setModel(const std::string &modelPath, const Model &model);

	private:
		ResourceStorage() = default;
	};
}

#endif //SURVIVE_RESOURCESTORAGE_H
