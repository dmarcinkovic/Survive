//
// Created by david on 14. 02. 2021..
//

#ifndef SURVIVE_PARTICLEMODEL_H
#define SURVIVE_PARTICLEMODEL_H


#include "../texture/TexturedModel.h"

struct ParticleModel
{
	TexturedModel texturedModel;
	unsigned rows;
	unsigned cols;

	ParticleModel(const TexturedModel &model, unsigned rows, unsigned cols);

	bool operator==(const ParticleModel &rhs) const;

	bool operator!=(const ParticleModel &rhs) const;
};

struct ParticleHash
{
	std::size_t operator()(const ParticleModel &particleModel) const noexcept
	{
		return particleModel.rows ^ particleModel.cols ^ TextureHash()(particleModel.texturedModel);
	}
};

#endif //SURVIVE_PARTICLEMODEL_H
