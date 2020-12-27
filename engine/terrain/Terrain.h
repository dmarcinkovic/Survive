//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_TERRAIN_H
#define SURVIVE_TERRAIN_H


#include "../entity/Entity.h"

class Terrain : public Entity
{
private:
	std::vector<Texture> m_Textures;

public:
	Terrain(const Model &model, const glm::vec3 &position, const glm::vec3 &scale);

	Terrain() = default;

	void addTextures(const char *blendMap, const std::vector<const char *> &textures);

	[[nodiscard]] const std::vector<Texture> &textures() const;
};


#endif //SURVIVE_TERRAIN_H
