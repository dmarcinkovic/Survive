//
// Created by david on 10. 02. 2021..
//

#ifndef SURVIVE_PARTICLETEXTURE_H
#define SURVIVE_PARTICLETEXTURE_H


#include "../texture/Texture.h"

class ParticleTexture
{
private:
	Texture m_Texture{};
	int m_Rows;

public:
	ParticleTexture(Texture texture, int numberOfRows);

	const Texture &getTexture() const;

	int getRows() const;

};


#endif //SURVIVE_PARTICLETEXTURE_H
