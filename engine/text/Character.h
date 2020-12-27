//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_CHARACTER_H
#define SURVIVE_CHARACTER_H

#include <vector>

struct Character
{
	int m_Id;
	float m_X, m_Y;
	float m_Width, m_Height;
	float m_XOffset, m_YOffset;
	float m_Advance;
	float m_ScaleW;
	float m_ScaleH;
	std::vector<float> m_TextureCoords;

	Character(int id, float x, float y, float width, float height, float xOffset, float yOffset, float advance,
			  float scaleW, float scaleH);

private:
	void calculateTextureCoordinates(float scaleW, float scaleH);
};


#endif //SURVIVE_CHARACTER_H
