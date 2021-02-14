//
// Created by david on 14. 02. 2021..
//

#ifndef SURVIVE_PARTICLEMODEL_H
#define SURVIVE_PARTICLEMODEL_H


#include "../texture/TexturedModel.h"

struct ParticleModel
{
	TexturedModel texturedModel;
	int rows;
	int cols;

	ParticleModel(const TexturedModel &model, int rows, int cols);
};


#endif //SURVIVE_PARTICLEMODEL_H
