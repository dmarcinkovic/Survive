//
// Created by david on 19. 12. 2020..
//

#ifndef SURVIVE_BLURRENDERER_H
#define SURVIVE_BLURRENDERER_H


#include <unordered_map>
#include "../texture/TexturedModel.h"
#include "../objects/Object3D.h"

class BlurRenderer
{
private:
	std::unordered_map<TexturedModel, std::vector<std::reference_wrapper<Object3D>>, TextureHash> m_Objects;


};


#endif //SURVIVE_BLURRENDERER_H
