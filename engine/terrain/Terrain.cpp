//
// Created by david on 22. 05. 2020..
//

#include "Terrain.h"

Terrain::Terrain(const Model &model, const glm::vec3 &position, const glm::vec3 &scale)
		: Entity(TexturedModel(model, 0), position, scale)
{

}

void Terrain::addTextures(const char *blendMap, const std::vector<const char *> &textures)
{
	m_Textures.emplace_back(Loader::loadTexture(blendMap));

	auto loadedTextures = Loader::loadAllTextures(textures);
	m_Textures.insert(m_Textures.end(), loadedTextures.begin(), loadedTextures.end());
}

const std::vector<Texture> &Terrain::textures() const
{
	return m_Textures;
}
