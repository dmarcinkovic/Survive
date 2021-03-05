//
// Created by david on 05. 03. 2021..
//

#ifndef SURVIVE_BLOOMCOMPONENT_H
#define SURVIVE_BLOOMCOMPONENT_H

struct BloomComponent
{
	Texture emissiveTexture{};
	float bloomStrength{};

	BloomComponent(const Texture &emissiveTexture, float bloomStrength)
			: emissiveTexture(emissiveTexture), bloomStrength(bloomStrength)
	{}

private:
	Texture m_BloomTexture{};
};

#endif //SURVIVE_BLOOMCOMPONENT_H
