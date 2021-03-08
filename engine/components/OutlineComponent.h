//
// Created by david on 08. 03. 2021..
//

#ifndef SURVIVE_OUTLINECOMPONENT_H
#define SURVIVE_OUTLINECOMPONENT_H

struct OutlineComponent
{
	bool drawOutline{};

	explicit OutlineComponent(bool drawOutline)
		: drawOutline(drawOutline)
	{}

	OutlineComponent() = default;
};

#endif //SURVIVE_OUTLINECOMPONENT_H
