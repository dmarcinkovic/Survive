//
// Created by david on 05. 09. 2021..
//

#ifndef SURVIVE_INSPECTOR_H
#define SURVIVE_INSPECTOR_H

#include <imgui.h>

namespace Survive
{
	class Inspector
	{
	public:
		Inspector();

		void draw(bool &open);
	};
}

#endif //SURVIVE_INSPECTOR_H
