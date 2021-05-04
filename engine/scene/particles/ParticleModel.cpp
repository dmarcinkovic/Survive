//
// Created by david on 14. 02. 2021..
//

#include "ParticleModel.h"

Survive::ParticleModel::ParticleModel(const TexturedModel &model, unsigned rows, unsigned cols)
		: texturedModel(model), rows(rows), cols(cols)
{

}

bool Survive::ParticleModel::operator==(const ParticleModel &rhs) const
{
	return texturedModel == rhs.texturedModel &&
		   rows == rhs.rows &&
		   cols == rhs.cols;
}

bool Survive::ParticleModel::operator!=(const ParticleModel &rhs) const
{
	return !(rhs == *this);
}
